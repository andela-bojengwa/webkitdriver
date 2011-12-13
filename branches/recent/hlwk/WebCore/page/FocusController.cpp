/*
 * Copyright (C) 2006, 2007 Apple Inc. All rights reserved.
 * Copyright (C) 2008 Nuanti Ltd.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "FocusController.h"

#include "AXObjectCache.h"
#include "Chrome.h"
#include "Document.h"
#include "Editor.h"
#include "EditorClient.h"
#include "Element.h"
#include "Event.h"
#include "EventHandler.h"
#include "EventNames.h"
#include "ExceptionCode.h"
#include "Frame.h"
#include "FrameTree.h"
#include "FrameView.h"
#include "HTMLFrameOwnerElement.h"
#include "HTMLNames.h"
#include "KeyboardEvent.h"
#include "Page.h"
#include "Range.h"
#include "RenderObject.h"
#include "RenderWidget.h"
#include "SelectionController.h"
#include "Settings.h"
#include "Widget.h"
#include <wtf/Platform.h>

namespace WebCore {

using namespace HTMLNames;

static inline void dispatchEventsOnWindowAndFocusedNode(Document* document, bool focused)
{
    // If we have a focused node we should dispatch blur on it before we blur the window.
    // If we have a focused node we should dispatch focus on it after we focus the window.
    // https://bugs.webkit.org/show_bug.cgi?id=27105
  
    // Do not fire events while modal dialogs are up.  See https://bugs.webkit.org/show_bug.cgi?id=33962
    if (document->page()->defersLoading())
        return;
    if (!focused && document->focusedNode())
        document->focusedNode()->dispatchBlurEvent();
    document->dispatchWindowEvent(Event::create(focused ? eventNames().focusEvent : eventNames().blurEvent, false, false));
    if (focused && document->focusedNode())
        document->focusedNode()->dispatchFocusEvent();
}

FocusController::FocusController(Page* page)
    : m_page(page)
    , m_isActive(false)
    , m_isFocused(false)
    , m_isChangingFocusedFrame(false)
{
}

void FocusController::setFocusedFrame(PassRefPtr<Frame> frame)
{
    if (m_focusedFrame == frame || m_isChangingFocusedFrame)
        return;

    m_isChangingFocusedFrame = true;

    RefPtr<Frame> oldFrame = m_focusedFrame;
    RefPtr<Frame> newFrame = frame;

    m_focusedFrame = newFrame;

    // Now that the frame is updated, fire events and update the selection focused states of both frames.
    if (oldFrame && oldFrame->view()) {
        oldFrame->selection()->setFocused(false);
        oldFrame->document()->dispatchWindowEvent(Event::create(eventNames().blurEvent, false, false));
    }

    if (newFrame && newFrame->view() && isFocused()) {
        newFrame->selection()->setFocused(true);
        newFrame->document()->dispatchWindowEvent(Event::create(eventNames().focusEvent, false, false));
    }

    m_isChangingFocusedFrame = false;
}

Frame* FocusController::focusedOrMainFrame()
{
    if (Frame* frame = focusedFrame())
        return frame;
    return m_page->mainFrame();
}

void FocusController::setFocused(bool focused)
{
    if (isFocused() == focused)
        return;
    
    m_isFocused = focused;
    
    if (m_focusedFrame && m_focusedFrame->view()) {
        m_focusedFrame->selection()->setFocused(focused);
        dispatchEventsOnWindowAndFocusedNode(m_focusedFrame->document(), focused);
    }
}

static Node* deepFocusableNode(FocusDirection direction, Node* node, KeyboardEvent* event)
{
    // The node we found might be a HTMLFrameOwnerElement, so descend down the frame tree until we find either:
    // 1) a focusable node, or
    // 2) the deepest-nested HTMLFrameOwnerElement
    while (node && node->isFrameOwnerElement()) {
        HTMLFrameOwnerElement* owner = static_cast<HTMLFrameOwnerElement*>(node);
        if (!owner->contentFrame())
            break;

        Document* document = owner->contentFrame()->document();

        node = (direction == FocusDirectionForward)
            ? document->nextFocusableNode(0, event)
            : document->previousFocusableNode(0, event);
        if (!node) {
            node = owner;
            break;
        }
    }

    return node;
}

bool FocusController::setInitialFocus(FocusDirection direction, KeyboardEvent* event)
{
    return advanceFocus(direction, event, true);
}

bool FocusController::advanceFocus(FocusDirection direction, KeyboardEvent* event, bool initialFocus)
{
    Frame* frame = focusedOrMainFrame();
    ASSERT(frame);
    Document* document = frame->document();

    Node* currentNode = document->focusedNode();
    // FIXME: Not quite correct when it comes to focus transitions leaving/entering the WebView itself
    bool caretBrowsing = focusedOrMainFrame()->settings()->caretBrowsingEnabled();

    if (caretBrowsing && !currentNode)
        currentNode = frame->selection()->start().node();

    document->updateLayoutIgnorePendingStylesheets();

    Node* node = (direction == FocusDirectionForward)
        ? document->nextFocusableNode(currentNode, event)
        : document->previousFocusableNode(currentNode, event);
            
    // If there's no focusable node to advance to, move up the frame tree until we find one.
    while (!node && frame) {
        Frame* parentFrame = frame->tree()->parent();
        if (!parentFrame)
            break;

        Document* parentDocument = parentFrame->document();

        HTMLFrameOwnerElement* owner = frame->ownerElement();
        if (!owner)
            break;

        node = (direction == FocusDirectionForward)
            ? parentDocument->nextFocusableNode(owner, event)
            : parentDocument->previousFocusableNode(owner, event);

        frame = parentFrame;
    }

    node = deepFocusableNode(direction, node, event);

    if (!node) {
        // We didn't find a node to focus, so we should try to pass focus to Chrome.
        if (!initialFocus && m_page->chrome()->canTakeFocus(direction)) {
            document->setFocusedNode(0);
            setFocusedFrame(0);
            m_page->chrome()->takeFocus(direction);
            return true;
        }

        // Chrome doesn't want focus, so we should wrap focus.
        Document* d = m_page->mainFrame()->document();
        node = (direction == FocusDirectionForward)
            ? d->nextFocusableNode(0, event)
            : d->previousFocusableNode(0, event);

        node = deepFocusableNode(direction, node, event);

        if (!node)
            return false;
    }

    ASSERT(node);

    if (node == document->focusedNode())
        // Focus wrapped around to the same node.
        return true;

    if (!node->isElementNode())
        // FIXME: May need a way to focus a document here.
        return false;

    if (node->isFrameOwnerElement()) {
        // We focus frames rather than frame owners.
        // FIXME: We should not focus frames that have no scrollbars, as focusing them isn't useful to the user.
        HTMLFrameOwnerElement* owner = static_cast<HTMLFrameOwnerElement*>(node);
        if (!owner->contentFrame())
            return false;

        document->setFocusedNode(0);
        setFocusedFrame(owner->contentFrame());
        return true;
    }
    
    // FIXME: It would be nice to just be able to call setFocusedNode(node) here, but we can't do
    // that because some elements (e.g. HTMLInputElement and HTMLTextAreaElement) do extra work in
    // their focus() methods.

    Document* newDocument = node->document();

    if (newDocument != document)
        // Focus is going away from this document, so clear the focused node.
        document->setFocusedNode(0);

    if (newDocument)
        setFocusedFrame(newDocument->frame());

    if (caretBrowsing) {
        VisibleSelection newSelection(Position(node, 0), Position(node, 0), DOWNSTREAM);
        if (frame->shouldChangeSelection(newSelection))
            frame->selection()->setSelection(newSelection);
    }

    static_cast<Element*>(node)->focus(false);
    return true;
}

static bool relinquishesEditingFocus(Node *node)
{
    ASSERT(node);
    ASSERT(node->isContentEditable());

    Node* root = node->rootEditableElement();
    Frame* frame = node->document()->frame();
    if (!frame || !root)
        return false;

    return frame->editor()->shouldEndEditing(rangeOfContents(root).get());
}

static void clearSelectionIfNeeded(Frame* oldFocusedFrame, Frame* newFocusedFrame, Node* newFocusedNode)
{
    if (!oldFocusedFrame || !newFocusedFrame)
        return;
        
    if (oldFocusedFrame->document() != newFocusedFrame->document())
        return;
    
    SelectionController* s = oldFocusedFrame->selection();
    if (s->isNone())
        return;

    bool caretBrowsing = oldFocusedFrame->settings()->caretBrowsingEnabled();
    if (caretBrowsing)
        return;

    Node* selectionStartNode = s->selection().start().node();
    if (selectionStartNode == newFocusedNode || selectionStartNode->isDescendantOf(newFocusedNode) || selectionStartNode->shadowAncestorNode() == newFocusedNode)
        return;
        
    if (Node* mousePressNode = newFocusedFrame->eventHandler()->mousePressNode())
        if (mousePressNode->renderer() && !mousePressNode->canStartSelection())
            if (Node* root = s->rootEditableElement())
                if (Node* shadowAncestorNode = root->shadowAncestorNode())
                    // Don't do this for textareas and text fields, when they lose focus their selections should be cleared
                    // and then restored when they regain focus, to match other browsers.
                    if (!shadowAncestorNode->hasTagName(inputTag) && !shadowAncestorNode->hasTagName(textareaTag))
                        return;
    
    s->clear();
}

bool FocusController::setFocusedNode(Node* node, PassRefPtr<Frame> newFocusedFrame)
{
    RefPtr<Frame> oldFocusedFrame = focusedFrame();
    RefPtr<Document> oldDocument = oldFocusedFrame ? oldFocusedFrame->document() : 0;
    
    Node* oldFocusedNode = oldDocument ? oldDocument->focusedNode() : 0;
    if (oldFocusedNode == node)
        return true;

    // FIXME: Might want to disable this check for caretBrowsing
    if (oldFocusedNode && oldFocusedNode->rootEditableElement() == oldFocusedNode && !relinquishesEditingFocus(oldFocusedNode))
        return false;
        
    clearSelectionIfNeeded(oldFocusedFrame.get(), newFocusedFrame.get(), node);
    
    if (!node) {
        if (oldDocument)
            oldDocument->setFocusedNode(0);
        m_page->editorClient()->setInputMethodState(false);
        return true;
    }

    RefPtr<Document> newDocument = node->document();

    if (newDocument && newDocument->focusedNode() == node) {
        m_page->editorClient()->setInputMethodState(node->shouldUseInputMethod());
        return true;
    }
    
    if (oldDocument && oldDocument != newDocument)
        oldDocument->setFocusedNode(0);
    
    setFocusedFrame(newFocusedFrame);
    
    if (newDocument)
        newDocument->setFocusedNode(node);
    
    m_page->editorClient()->setInputMethodState(node->shouldUseInputMethod());

    return true;
}

void FocusController::setActive(bool active)
{
    if (m_isActive == active)
        return;

    m_isActive = active;

    if (FrameView* view = m_page->mainFrame()->view()) {
        if (!view->platformWidget()) {
            view->layoutIfNeededRecursive();
            view->updateControlTints();
        }
    }

    focusedOrMainFrame()->selection()->pageActivationChanged();
    
    if (m_focusedFrame && isFocused())
        dispatchEventsOnWindowAndFocusedNode(m_focusedFrame->document(), active);
}

} // namespace WebCore
