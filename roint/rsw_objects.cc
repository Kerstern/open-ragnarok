/* $Id$ */
/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of The Open Ragnarok Project
    Copyright 2007 - 2009 The Open Ragnarok Team
    For the latest information visit http://www.open-ragnarok.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
*/
#include "stdafx.h"
#include "ro/types/rsw.h"
#include "ro/ro.h"

// ===== OBJECT
RO::RSW::RSMObject::RSMObject(RO::RSW::ObjectType t) {
	m_type = t;
}

RO::RSW::RSMObject::~RSMObject() {
}

RO::RSW::ObjectType RO::RSW::RSMObject::getType() const {
	return(m_type);
}

bool RO::RSW::RSMObject::isType(RO::RSW::ObjectType t) const {
	return(m_type == t);
}

void RO::RSW::RSMObject::Dump(std::ostream& o, const std::string& pfx) const {
	o << pfx << "No data to dump" << std::endl;
}

void RO::RSW::RSMObject::Dump(std::ostream& o) const {
	Dump(o, "");
}

RO::RSW::RSMObject* RO::RSW::RSMObject::Copy() const {
	RSMObject* ret = NULL;
	switch(m_type) {
		case OT_Model:
			ret = new Model((Model*)this);
			break;
		case OT_Light:
			ret = new Light((Light*)this);
			break;
		case OT_Sound:
			ret = (RSMObject*)new Sound((Sound*)this);
			break;
		case OT_Effect:
			ret = (RSMObject*)new Effect((Effect*)this);
			break;
		case OT_Unknown:
		default:
			ret = NULL;
			break;
	}

	return(ret);
}

void RO::RSW::RSMObject::Copy(const RSMObject& o) {
	if (!isType(o.m_type))
		return;
	switch(m_type) {
		case OT_Unknown:
			break;
		case OT_Model:
			{
				Model* m = (Model*)this;
				*m = (const Model*)&o;
			}
			break;
		case OT_Light:
			{
				Light* l = (Light*)this;
				*l = (const Light*)&o;
			}
			break;
		case OT_Sound:
			{
				Sound* s = (Sound*)this;
				*s = (const Sound*)&o;
			}
			break;
		case OT_Effect:
			{
				Effect* e = (Effect*)this;
				*e = (const Effect*)&o;
			}
			break;
	}
}

// ===== MODEL
RO::RSW::Model::Model() : RSMObject(RO::RSW::OT_Model) {
	memset(&m_data, 0, sizeof(ModelData));
	data = &m_data;
}

RO::RSW::Model::Model(const Model& mdl) : RSMObject(RO::RSW::OT_Model) {
	data = &m_data;
	memcpy(&m_data, &mdl.m_data, sizeof(ModelData));
}

RO::RSW::Model::Model(const Model* mdl) : RSMObject(RO::RSW::OT_Model) {
	data = &m_data;
	memcpy(&m_data, &mdl->m_data, sizeof(ModelData));
}

RO::RSW::Model::~Model() {
}

bool RO::RSW::Model::readStream(std::istream& s) {
	s.read((char*)&m_data, sizeof(ModelData));
	return(true);
}

bool RO::RSW::Model::writeStream(std::ostream& s) const {
	s.write((char*)&m_type, sizeof(int));
	s.write((char*)&m_data, sizeof(ModelData));
	return(true);
}

void RO::RSW::Model::Dump(std::ostream& o, const std::string& pfx) const {
	char buf[512];
	o << pfx << "Model " << m_data.filename << std::endl;
	o << pfx << "\t" << m_data.m_name << std::endl;
	sprintf(buf, "pos: %.2f, %.2f, %.2f", m_data.pos[0], m_data.pos[1], m_data.pos[2]);
	o << pfx << "\t" << buf << std::endl;
	sprintf(buf, "rot: %.2f, %.2f, %.2f", m_data.rot[0], m_data.rot[1], m_data.rot[2]);
	o << pfx << "\t" << buf << std::endl;
	sprintf(buf, "scale: %.2f, %.2f, %.2f", m_data.scale[0], m_data.scale[1], m_data.scale[2]);
	o << pfx << "\t" << buf << std::endl;
}

const char* RO::RSW::Model::getName() const {
	return(m_data.m_name);
}

RO::RSW::Model& RO::RSW::Model::operator = (const Model& m) {
	memcpy(&m_data, &m.m_data, sizeof(ModelData));
	return(*this);
}

RO::RSW::Model& RO::RSW::Model::operator = (const Model* m) {
	memcpy(&m_data, &m->m_data, sizeof(ModelData));
	return(*this);
}


// ===== LIGHT
RO::RSW::Light::Light() : RSMObject(RO::RSW::OT_Light) {
	memset(&m_data, 0, sizeof(LightData));
	data = &m_data;
}

RO::RSW::Light::Light(const Light& l) : RSMObject(RO::RSW::OT_Light) {
	Copy(l);
}

RO::RSW::Light::Light(const Light* l) : RSMObject(RO::RSW::OT_Light) {
	Copy(*l);
}

RO::RSW::Light::~Light() {
}

bool RO::RSW::Light::readStream(std::istream& s) {
	s.read((char*)&m_data, sizeof(LightData));
	return(true);
}

bool RO::RSW::Light::writeStream(std::ostream& s) const {
	s.write((char*)&m_type, sizeof(int));
	s.write((char*)&m_data, sizeof(LightData));
	return(true);
}

const char* RO::RSW::Light::getName() const {
	return(m_data.name);
}

RO::RSW::Light& RO::RSW::Light::operator = (const Light& o) {
	memcpy(&m_data, &o.m_data, sizeof(LightData));
	return(*this);
}

RO::RSW::Light& RO::RSW::Light::operator = (const Light* o) {
	memcpy(&m_data, &o->m_data, sizeof(LightData));
	return(*this);
}


// ===== SOUND
RO::RSW::Sound::Sound() : RSMObject(RO::RSW::OT_Sound) {
	memset(&m_data, 0, sizeof(SoundData));
	data = &m_data;
}

RO::RSW::Sound::Sound(const Sound& l) : RSMObject(RO::RSW::OT_Sound) {
	Copy(l);
}

RO::RSW::Sound::Sound(const Sound* l) : RSMObject(RO::RSW::OT_Sound) {
	Copy(*l);
}

RO::RSW::Sound::~Sound() {
}

bool RO::RSW::Sound::readStream(std::istream& s) {
	s.read((char*)&m_data, sizeof(SoundData));
	return(true);
}

bool RO::RSW::Sound::writeStream(std::ostream& s) const {
	s.write((char*)&m_type, sizeof(int));
	s.write((char*)&m_data, sizeof(SoundData));
	return(true);
}

const char* RO::RSW::Sound::getName() const {
	return(m_data.name);
}

RO::RSW::Sound& RO::RSW::Sound::operator = (const Sound& o) {
	memcpy(&m_data, &o.m_data, sizeof(SoundData));
	return(*this);
}

RO::RSW::Sound& RO::RSW::Sound::operator = (const Sound* o) {
	memcpy(&m_data, &o->m_data, sizeof(SoundData));
	return(*this);
}

// ===== EFFECT
RO::RSW::Effect::Effect() : RSMObject(RO::RSW::OT_Effect) {
	memset(&m_data, 0, sizeof(EffectData));
	data = &m_data;
}


RO::RSW::Effect::Effect(const Effect& l) : RSMObject(RO::RSW::OT_Effect) {
	Copy(l);
}

RO::RSW::Effect::Effect(const Effect* l) : RSMObject(RO::RSW::OT_Effect) {
	Copy(*l);
}

RO::RSW::Effect::~Effect() {
}

bool RO::RSW::Effect::readStream(std::istream& s) {
	s.read((char*)&m_data, sizeof(EffectData));
	return(true);
}

bool RO::RSW::Effect::writeStream(std::ostream& s) const {
	s.write((char*)&m_type, sizeof(int));
	s.write((char*)&m_data, sizeof(EffectData));
	return(true);
}

const char* RO::RSW::Effect::getName() const {
	return(m_data.name);
}

RO::RSW::Effect& RO::RSW::Effect::operator = (const Effect& o) {
	memcpy(&m_data, &o.m_data, sizeof(EffectData));
	return(*this);
}

RO::RSW::Effect& RO::RSW::Effect::operator = (const Effect* o) {
	memcpy(&m_data, &o->m_data, sizeof(EffectData));
	return(*this);
}
