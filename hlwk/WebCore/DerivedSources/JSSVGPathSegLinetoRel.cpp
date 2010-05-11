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

#if ENABLE(SVG)

#include "JSSVGPathSegLinetoRel.h"

#include "SVGPathSegLineto.h"
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegLinetoRel);

/* Hash table */

static const HashTableValue JSSVGPathSegLinetoRelTableValues[4] =
{
    { "x", DontDelete, (intptr_t)jsSVGPathSegLinetoRelX, (intptr_t)setJSSVGPathSegLinetoRelX },
    { "y", DontDelete, (intptr_t)jsSVGPathSegLinetoRelY, (intptr_t)setJSSVGPathSegLinetoRelY },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGPathSegLinetoRelConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegLinetoRelTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGPathSegLinetoRelTableValues, 0 };
#else
    { 9, 7, JSSVGPathSegLinetoRelTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGPathSegLinetoRelConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegLinetoRelConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegLinetoRelConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegLinetoRelConstructorTableValues, 0 };
#endif

class JSSVGPathSegLinetoRelConstructor : public DOMConstructorObject {
public:
    JSSVGPathSegLinetoRelConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGPathSegLinetoRelConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGPathSegLinetoRelPrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGPathSegLinetoRelConstructor::s_info = { "SVGPathSegLinetoRelConstructor", 0, &JSSVGPathSegLinetoRelConstructorTable, 0 };

bool JSSVGPathSegLinetoRelConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegLinetoRelConstructor, DOMObject>(exec, &JSSVGPathSegLinetoRelConstructorTable, this, propertyName, slot);
}

bool JSSVGPathSegLinetoRelConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPathSegLinetoRelConstructor, DOMObject>(exec, &JSSVGPathSegLinetoRelConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegLinetoRelPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegLinetoRelPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegLinetoRelPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegLinetoRelPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegLinetoRelPrototype::s_info = { "SVGPathSegLinetoRelPrototype", 0, &JSSVGPathSegLinetoRelPrototypeTable, 0 };

JSObject* JSSVGPathSegLinetoRelPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSegLinetoRel>(exec, globalObject);
}

const ClassInfo JSSVGPathSegLinetoRel::s_info = { "SVGPathSegLinetoRel", &JSSVGPathSeg::s_info, &JSSVGPathSegLinetoRelTable, 0 };

JSSVGPathSegLinetoRel::JSSVGPathSegLinetoRel(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGPathSegLinetoRel> impl)
    : JSSVGPathSeg(structure, globalObject, impl)
{
}

JSObject* JSSVGPathSegLinetoRel::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegLinetoRelPrototype(JSSVGPathSegLinetoRelPrototype::createStructure(JSSVGPathSegPrototype::self(exec, globalObject)));
}

bool JSSVGPathSegLinetoRel::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegLinetoRel, Base>(exec, &JSSVGPathSegLinetoRelTable, this, propertyName, slot);
}

bool JSSVGPathSegLinetoRel::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPathSegLinetoRel, Base>(exec, &JSSVGPathSegLinetoRelTable, this, propertyName, descriptor);
}

JSValue jsSVGPathSegLinetoRelX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegLinetoRel* castedThis = static_cast<JSSVGPathSegLinetoRel*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegLinetoRel* imp = static_cast<SVGPathSegLinetoRel*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->x());
    return result;
}

JSValue jsSVGPathSegLinetoRelY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegLinetoRel* castedThis = static_cast<JSSVGPathSegLinetoRel*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegLinetoRel* imp = static_cast<SVGPathSegLinetoRel*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->y());
    return result;
}

JSValue jsSVGPathSegLinetoRelConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegLinetoRel* domObject = static_cast<JSSVGPathSegLinetoRel*>(asObject(slot.slotBase()));
    return JSSVGPathSegLinetoRel::getConstructor(exec, domObject->globalObject());
}
void JSSVGPathSegLinetoRel::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPathSegLinetoRel, Base>(exec, propertyName, value, &JSSVGPathSegLinetoRelTable, this, slot);
}

void setJSSVGPathSegLinetoRelX(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegLinetoRel* castedThisObj = static_cast<JSSVGPathSegLinetoRel*>(thisObject);
    SVGPathSegLinetoRel* imp = static_cast<SVGPathSegLinetoRel*>(castedThisObj->impl());
    imp->setX(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

void setJSSVGPathSegLinetoRelY(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegLinetoRel* castedThisObj = static_cast<JSSVGPathSegLinetoRel*>(thisObject);
    SVGPathSegLinetoRel* imp = static_cast<SVGPathSegLinetoRel*>(castedThisObj->impl());
    imp->setY(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

JSValue JSSVGPathSegLinetoRel::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGPathSegLinetoRelConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}

#endif // ENABLE(SVG)