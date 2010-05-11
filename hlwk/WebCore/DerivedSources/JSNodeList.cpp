/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSNodeList.h"

#include "AtomicString.h"
#include "ExceptionCode.h"
#include "JSNode.h"
#include "Node.h"
#include "NodeList.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/PropertyNameArray.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSNodeList);

/* Hash table */

static const HashTableValue JSNodeListTableValues[3] =
{
    { "length", DontDelete|ReadOnly, (intptr_t)jsNodeListLength, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsNodeListConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSNodeListTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSNodeListTableValues, 0 };
#else
    { 5, 3, JSNodeListTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSNodeListConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSNodeListConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSNodeListConstructorTableValues, 0 };
#else
    { 1, 0, JSNodeListConstructorTableValues, 0 };
#endif

class JSNodeListConstructor : public DOMConstructorObject {
public:
    JSNodeListConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSNodeListConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSNodeListPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSNodeListConstructor::s_info = { "NodeListConstructor", 0, &JSNodeListConstructorTable, 0 };

bool JSNodeListConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSNodeListConstructor, DOMObject>(exec, &JSNodeListConstructorTable, this, propertyName, slot);
}

bool JSNodeListConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSNodeListConstructor, DOMObject>(exec, &JSNodeListConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSNodeListPrototypeTableValues[2] =
{
    { "item", DontDelete|Function, (intptr_t)jsNodeListPrototypeFunctionItem, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSNodeListPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSNodeListPrototypeTableValues, 0 };
#else
    { 2, 1, JSNodeListPrototypeTableValues, 0 };
#endif

const ClassInfo JSNodeListPrototype::s_info = { "NodeListPrototype", 0, &JSNodeListPrototypeTable, 0 };

JSObject* JSNodeListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSNodeList>(exec, globalObject);
}

bool JSNodeListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSNodeListPrototypeTable, this, propertyName, slot);
}

bool JSNodeListPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSNodeListPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSNodeList::s_info = { "NodeList", 0, &JSNodeListTable, 0 };

JSNodeList::JSNodeList(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<NodeList> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSNodeList::~JSNodeList()
{
    forgetDOMObject(this, impl());
}

JSObject* JSNodeList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSNodeListPrototype(JSNodeListPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSNodeList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    const HashEntry* entry = JSNodeListTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<NodeList*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }
    if (canGetItemsForName(exec, static_cast<NodeList*>(impl()), propertyName)) {
        slot.setCustom(this, nameGetter);
        return true;
    }
    return getStaticValueSlot<JSNodeList, Base>(exec, &JSNodeListTable, this, propertyName, slot);
}

bool JSNodeList::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    const HashEntry* entry = JSNodeListTable.entry(exec, propertyName);
    if (entry) {
        PropertySlot slot;
        slot.setCustom(this, entry->propertyGetter());
        descriptor.setDescriptor(slot.getValue(exec, propertyName), entry->attributes());
        return true;
    }
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<NodeList*>(impl())->length()) {
        PropertySlot slot;
        slot.setCustomIndex(this, index, indexGetter);
        descriptor.setDescriptor(slot.getValue(exec, propertyName), DontDelete | ReadOnly);
        return true;
    }
    if (canGetItemsForName(exec, static_cast<NodeList*>(impl()), propertyName)) {
        PropertySlot slot;
        slot.setCustom(this, nameGetter);
        descriptor.setDescriptor(slot.getValue(exec, propertyName), ReadOnly | DontDelete | DontEnum);
        return true;
    }
    return getStaticValueDescriptor<JSNodeList, Base>(exec, &JSNodeListTable, this, propertyName, descriptor);
}

bool JSNodeList::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<NodeList*>(impl())->length()) {
        slot.setCustomIndex(this, propertyName, indexGetter);
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

JSValue jsNodeListLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSNodeList* castedThis = static_cast<JSNodeList*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    NodeList* imp = static_cast<NodeList*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->length());
    return result;
}

JSValue jsNodeListConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSNodeList* domObject = static_cast<JSNodeList*>(asObject(slot.slotBase()));
    return JSNodeList::getConstructor(exec, domObject->globalObject());
}
void JSNodeList::getOwnPropertyNames(ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    for (unsigned i = 0; i < static_cast<NodeList*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getOwnPropertyNames(exec, propertyNames, mode);
}

JSValue JSNodeList::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSNodeListConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsNodeListPrototypeFunctionItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSNodeList::s_info))
        return throwError(exec, TypeError);
    JSNodeList* castedThisObj = static_cast<JSNodeList*>(asObject(thisValue));
    NodeList* imp = static_cast<NodeList*>(castedThisObj->impl());
    int index = args.at(0).toInt32(exec);
    if (index < 0) {
        setDOMException(exec, INDEX_SIZE_ERR);
        return jsUndefined();
    }


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), WTF::getPtr(imp->item(index)));
    return result;
}


JSValue JSNodeList::indexGetter(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSNodeList* thisObj = static_cast<JSNodeList*>(asObject(slot.slotBase()));
    return toJS(exec, thisObj->globalObject(), static_cast<NodeList*>(thisObj->impl())->item(slot.index()));
}
JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, NodeList* object)
{
    return getDOMObjectWrapper<JSNodeList>(exec, globalObject, object);
}
NodeList* toNodeList(JSC::JSValue value)
{
    return value.inherits(&JSNodeList::s_info) ? static_cast<JSNodeList*>(asObject(value))->impl() : 0;
}

}