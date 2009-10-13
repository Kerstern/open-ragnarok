/* $Id: desktop_login.cc 146 2009-09-29 19:47:17Z kr105 $ */
#include "stdafx.h"

#include "desktop_ingame.h"

DesktopIngame::DesktopIngame(OpenRO* ro) : RODesktop("ui\\ingame.xml", ro) {
	ADD_HANDLER("stats_window/btnMap", evtClick, DesktopIngame::handleBtnMap);
	ADD_HANDLER("chatwindow/btnNext", evtClick, DesktopIngame::handleBtnNpcNext);
	ADD_HANDLER("chatwindow/btnCancel", evtClick, DesktopIngame::handleBtnNpcClose);

	m_hp = m_maxhp = 0;
	m_sp = m_maxsp = 0;
	m_weight = m_maxweight = m_zeny = 0;

	minimap = (GUI::Window*)getElement("minimap");
	chatwindow = (GUI::ChatWindow*)getElement("chatwindow");
	
	m_npc_answered = false;
}

void DesktopIngame::updateHP() {
	GUI::ProgressBar* bar;
	GUI::Label* lbl;
	char buf[32];

	bar = (GUI::ProgressBar*)getElement("stats_window/hp");
	lbl = (GUI::Label*)getElement("stats_window/hp_text");

	sprintf(buf, "%d / %d", m_hp, m_maxhp);

	bar->setValue(m_hp);
	bar->setMaxValue(m_maxhp);
	lbl->setText(buf);
}

void DesktopIngame::updateSP() {
	GUI::ProgressBar* bar;
	GUI::Label* lbl;
	char buf[32];

	bar = (GUI::ProgressBar*)getElement("stats_window/sp");
	lbl = (GUI::Label*)getElement("stats_window/sp_text");

	sprintf(buf, "%d / %d", m_sp, m_maxsp);

	bar->setValue(m_sp);
	bar->setMaxValue(m_maxsp);
	lbl->setText(buf);
}

void DesktopIngame::updateStatus() {
	char buf[64];
	GUI::Label* lbl = (GUI::Label*)getElement("stats_window/status");

	sprintf(buf, "weight: %.0f / %.0f Zeny: %d", m_weight, m_maxweight, m_zeny);

	lbl->setText(buf);
}

void DesktopIngame::setHP(unsigned short hp) {
	if (hp == m_hp)
		return;
	m_hp = hp;
	updateHP();
}

void DesktopIngame::setHP(unsigned short hp, unsigned short maxhp) {
	if (hp == m_hp && maxhp == m_maxhp)
		return;
	m_hp = hp;
	m_maxhp = maxhp;
	updateHP();
}

void DesktopIngame::setMaxHP(unsigned short maxhp) {
	if (maxhp == m_maxhp)
		return;
	m_maxhp = maxhp;
	updateHP();
}

void DesktopIngame::setSP(unsigned short sp) {
	if (sp == m_sp)
		return;
	m_sp = sp;
	updateSP();
}

void DesktopIngame::setSP(unsigned short sp, unsigned short maxsp) {
	if (sp == m_sp && maxsp == m_maxsp)
		return;
	m_sp = sp;
	m_maxsp = maxsp;
	updateSP();
}

void DesktopIngame::setMaxSP(unsigned short maxsp) {
	if (maxsp == m_maxsp)
		return;
	m_maxsp = maxsp;
	updateSP();
}

void DesktopIngame::setWeight(float weight) {
	if (m_weight == weight)
		return;
	m_weight = weight;
	updateStatus();
}

void DesktopIngame::setWeight(float weight, float maxweight) {
	if (m_weight == weight && m_maxweight == maxweight)
		return;
	m_weight = weight;
	m_maxweight = maxweight;
	updateStatus();
}

void DesktopIngame::setMaxWeight(float maxweight) {
	if (m_maxweight == maxweight)
		return;
	m_maxweight = maxweight;
	updateStatus();
}

void DesktopIngame::setZeny(unsigned int zeny) {
	if (m_zeny == zeny)
		return;
	m_zeny = zeny;
	updateStatus();
}


bool DesktopIngame::handleBtnNpcClose(GUI::Event&) {
	//m_ro->NpcClose();
	chatwindow->setVisible(false);
	//m_npc_answered = true;
	return(true);
}

bool DesktopIngame::handleBtnNpcNext(GUI::Event&) {
	m_ro->NpcContinue();
	m_npc_answered = true;
	return(true);
}

bool DesktopIngame::handleBtnMap(GUI::Event&) {
	minimap->setVisible(!minimap->isVisible());

	return(true);
}

void DesktopIngame::AddNpcLine(std::string line) {
	if (!chatwindow->isVisible()) {
		chatwindow->setVisible(true);
		chatwindow->Clear();
		getElement("chatwindow/btnNext")->setVisible(false);
	}
	if (m_npc_answered == true) {
		chatwindow->Clear();
		m_npc_answered = false;
	}
	chatwindow->Add(line);
}

void DesktopIngame::AddNpcNextBtn() {
	getElement("chatwindow/btnNext")->setVisible(true);
}

void DesktopIngame::afterDraw(unsigned int delay) {

	elapsed += delay;
	ptick += delay;
	ffps += delay;

	if(ffps >= 1000){
		printf("FPS: %d aprox\t\t\r", fps);
		ffps = 0;
		fps = 0;
	}else
		fps++;


	//Keep Alive packet to CharServer
	if(ptick >= 12000){
		m_ro->KeepAliveMap();
		ptick = 0;
	}
}

void DesktopIngame::setMinimap(sdle::Texture& tex) {
	minimap->setTexture(tex);
}
