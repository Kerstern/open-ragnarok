/* $Id$ */
#include "stdafx.h"

#include "rogl/actgl.h"

namespace rogl {

ActGL::ActGL() {
	act = NULL;
	ext = NULL;
	m_action = 0;
	m_delay = 0;
	m_frame = 0;
}

ActGL::ActGL(const ActGL& _act) {
	*this = _act;
}

ActGL::~ActGL() {
}

void ActGL::setAction(unsigned short a) {
	m_action = a;
}


bool ActGL::valid() const {
	return(act != NULL);
}


void ActGL::Draw() const {
}


void ActGL::Draw(unsigned long delay, RO::CDir direction) {
	m_delay += delay;
	while (m_delay > 200) {
		m_delay -= 200;
		m_frame++;
	}

	glPushMatrix();

	// Cylindrical Billboard
	// Credits: http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat1
	float modelview[16];
	int i,j;
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
	for (i = 0; i < 3; i += 2)
		for (j = 0; j < 3; j++)
			if (i == j)
				modelview[i * 4 + j] = 1.0f;
			else
				modelview[i * 4 + j] = 0.0f;
	glLoadMatrixf(modelview);
	// End billboard


	spr.getTexture().Activate();
	const RO::ACT::Action& a = act->getAction(m_action * 8 + direction);
	if(m_frame >= a.getMotionCount()) {
		m_frame = m_frame % a.getMotionCount();
	}
	const RO::ACT::Motion& p = a.getMotion(m_frame);
	float u[2], v[2];
	//float aux;
	int sprcount = p.getClipCount();
	int w, h;

	for (int i = 0; i < sprcount; i++) {
		const RO::ACT::SprClip& s = p.getClip(i);
		if (s.sprNo < 0) {
			continue;
		}
		w = s.w;
		h = s.h;

		const rogl::sprInfo& info = spr.getFrameInfo(s.sprNo);
		if (w == 0)
			w = info.w;
		if (h == 0)
			h = info.h;

		// Setup coordinates
		v[0] = info.sv;
		v[1] = info.ev;
		if (s.mirrorOn) {
			u[0] = info.su;
			u[1] = info.eu;
		}
		else {
			u[0] = info.eu;
			u[1] = info.su;
		}

		float x[2];
		float y[2];

		x[0] =  (float)s.x - 5.0f;
		x[1] =  x[0] + w;

		y[0] =  (float)s.y + (float)h / 2.0f;
		y[1] =  y[0] + (float)h;

		// Set things straight
		x[0] = x[0] / 10.0f - 2.5f; // 2.5f = half of a gat tile.
		x[1] = x[1] / 10.0f - 2.5f;
		y[0] /= 10.0f;
		y[1] /= 10.0f;

		// Draw
		glBegin(GL_QUADS);
		glTexCoord2f(u[0], v[1]); glVertex3f(x[0], y[0], 0.0f);
		glTexCoord2f(u[0], v[0]); glVertex3f(x[0], y[1], 0.0f);
		glTexCoord2f(u[1], v[0]); glVertex3f(x[1], y[1], 0.0f);
		glTexCoord2f(u[1], v[1]); glVertex3f(x[1], y[0], 0.0f);
		glEnd();
	}

	//spr.Draw(m_frame, true);
	if (ext != NULL) {
		if (p.attachPoints.size() > 0)
			glTranslatef((float)p.attachPoints[0].x / 10.0f, (float)p.attachPoints[0].y / 10.0f, 0.0f);
		ext->Draw(delay);
	}
	glColor3f(1,0,0);
	Cross(10);
	glColor3f(1,1,1);
	glPopMatrix();
}

ActGL& ActGL::operator = (const ActGL& _act) {
	this->act = _act.act;
	this->spr = _act.spr;
	this->ext = _act.ext;
	return(*this);
}

void ActGL::setExt(ActGL* e) {
	ext = e;
}

void ActGL::setAct(RO::ACT* a) {
	act = a;
}

void ActGL::setSpr(const SprGL& s) {
	spr = s;
}

ActGL* ActGL::getExt() {
	return(ext);
}

RO::ACT* ActGL::getAct() {
	return(act);
}

SprGL& ActGL::getSpr() {
	return(spr);
}


void ActGL::Cross(float size) {
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	glVertex3f(- size, 0,0);
	glVertex3f(+ size, 0,0);
	glVertex3f(0, - size,0);
	glVertex3f(0, + size,0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}


}