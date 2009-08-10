/* $Id$ */
#ifndef __GUI_TEXTINPUT_H
#define __GUI_TEXTINPUT_H

#include "label.h"
#define TEXT_LEN		1024	//�ַ�����󳤶�

namespace GUI {
	typedef struct 
	{
		int startPos;
		int endPos;
	}LINEINFO;

	class TextInput : public Label {
	protected:
		static unsigned int cursor_delay;//��ǰ�����˸�ȴ�ʱ��
		unsigned int m_pos;
		unsigned int m_start;
		unsigned int m_delay;
		bool m_bar,actived,m_MouseDown;

		int m_charpos;

		int GetcharposNum();
		int GetcharposNum(int charpos);

	public:
		TextInput(Element* parent, const TiXmlElement*, TextureManager&, FileManager&);

		virtual void Draw(unsigned int delay = 0);
		virtual void onGetFocus();
		virtual void onLoseFocus();
		virtual bool HandleKeyDown(int key, int mod = 0);
		virtual bool HandleMouseDown(int x, int y, int button);
	};
}

#endif /* __GUI_TEXTINPUT_H */
