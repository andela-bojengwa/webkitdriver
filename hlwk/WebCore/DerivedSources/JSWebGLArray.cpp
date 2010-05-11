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

#if ENABLE(3D_CANVAS)

#include "JSWebGLArray.h"

#include "JSWebGLArray.h"
#include "JSWebGLArrayBuffer.h"
#include "WebGLArray.h"
#include "WebGLArrayBuffer.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSWebGLArray);

/* Hash table */

static const HashTableValue JSWebGLArrayTableValues[5] =
{
    { "buffer", DontDelete|ReadOnly, (intptr_t)jsWebGLArrayBuffer, (intptr_t)0 },
    { "byteOffset", DontDelete|ReadOnly, (intptr_t)jsWebGLArrayByteOffset, (intptr_t)0 },
    { "byteLength", DontDelete|ReadOnly, (intptr_t)jsWebGLArrayByteLength, (intptr_t)0 },
    { "length", DontDelete|ReadOnly, (intptr_t)jsWebGLArrayLength, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWebGLArrayTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSWebGLArrayTableValues, 0 };
#else
    { 8, 7, JSWebGLArrayTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSWebGLArrayPrototypeTableValues[2] =
{
    { "slice", DontDelete|Function, (intptr_t)jsWebGLArrayPrototypeFunctionSlice, (intptr_t)2 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWebGLArrayPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSWebGLArrayPrototypeTableValues, 0 };
#else
    { 2, 1, JSWebGLArrayPrototypeTableValues, 0 };
#endif

const ClassInfo JSWebGLArrayPrototype::s_info = { "WebGLArrayPrototype", 0, &JSWebGLArrayPrototypeTable, 0 };

JSObject* JSWebGLArrayPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSWebGLArray>(exec, globalObject);
}

bool JSWebGLArrayPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSWebGLArrayPrototypeTable, this, propertyName, slot);
}

bool JSWebGLArrayPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSWebGLArrayPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSWebGLArray::s_info = { "WebGLArray", 0, &JSWebGLArrayTable, 0 };

JSWebGLArray::JSWebGLArray(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<WebGLArray> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSWebGLArray::~JSWebGLArray()
{
    forgetDOMObject(this, impl());
}

JSObject* JSWebGLArray::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSWebGLArrayPrototype(JSWebGLArrayPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSWebGLArray::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWebGLArray, Base>(exec, &JSWebGLArrayTable, this, propertyName, slot);
}

bool JSWebGLArray::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWebGLArray, Base>(exec, &JSWebGLArrayTable, this, propertyName, descriptor);
}

JSValue jsWebGLArrayBuffer(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWebGLArray* castedThis = static_cast<JSWebGLArray*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WebGLArray* imp = static_cast<WebGLArray*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->buffer()));
    return result;
}

JSValue jsWebGLArrayByteOffset(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWebGLArray* castedThis = static_cast<JSWebGLArray*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WebGLArray* imp = static_cast<WebGLArray*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->byteOffset());
    return result;
}

JSValue jsWebGLArrayByteLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWebGLArray* castedThis = static_cast<JSWebGLArray*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WebGLArray* imp = static_cast<WebGLArray*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->byteLength());
    return result;
}

JSValue jsWebGLArrayLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWebGLArray* castedThis = static_cast<JSWebGLArray*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WebGLArray* imp = static_cast<WebGLArray*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->length());
    return result;
}

JSValue JSC_HOST_CALL jsWebGLArrayPrototypeFunctionSlice(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSWebGLArray::s_info))
        return throwError(exec, TypeError);
    JSWebGLArray* castedThisObj = static_cast<JSWebGLArray*>(asObject(thisValue));
    WebGLArray* imp = static_cast<WebGLArray*>(castedThisObj->impl());
    unsigned offset = args.at(0).toInt32(exec);
    unsigned length = args.at(1).toInt32(exec);


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), WTF::getPtr(imp->slice(offset, length)));
    return result;
}

WebGLArray* toWebGLArray(JSC::JSValue value)
{
    return value.inherits(&JSWebGLArray::s_info) ? static_cast<JSWebGLArray*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(3D_CANVAS)