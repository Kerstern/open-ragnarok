/* $Id$ */
#ifndef __GUI_TEXTINPUT_H
#define __GUI_TEXTINPUT_H

#include "label.h"
#include "sdle/font.h"

typedef struct _Node {
        LCHAR Ch;
		bool  selected;
        
        struct _Node *Prev;
        struct _Node *Next;
		SDL_Surface *Font_Screen;
}NODE;

typedef struct _TextEditor {
	SDL_Surface	*Surface;           //Ŀ�����
	sdle::Font	*Font;              //����

	NODE		*Head;             //һ�����ֵĿ�ʼ
	NODE		*Start;            //һ�����ֵĿ�ʼ
	NODE		*Current;          //��ǰ�ڵ�, �����ҵȼ��ƶ��˽ڵ�
	NODE		*select1;          //��סѡ����1
	NODE		*select2;          //��סѡ����2
        
	bool		Text_Changed;      //�ļ��Ƿ��Ѹı�, FALSEû�иı�, TURE�Ѹı�       
        
	Sint16		x;
	Sint16		y;
	Sint16		z;
	Sint32		Len;
	int         EffectWidth;
	LCHAR		*m_text;
	Uint32		FColor;
	Uint32		BColor;
	Uint32		SFColor;
	Uint32		SBColor;
	Uint8		Alpha;
}TextEditor;

namespace GUI {

typedef struct {
	int startPos;
	int endPos;
}LINEINFO;

/** GUI object for inputing text */
class TextInput : public Label {
protected:
	static unsigned int cursor_delay;//��ǰ�����˸�ȴ�ʱ��
	/** Cursor Position */
	unsigned int m_pos;
	/** Cursor selection start */
	unsigned int m_start;
	unsigned int m_delay;
	bool m_bar,actived,m_MouseDown;

public:
	TextEditor G_Text;
	bool       SelectFlag;

	TextInput(Element* parent, const TiXmlElement*, TextureManager&, FileManager&);
	~TextInput();

	/** Draws the control
	 * @param delay ticks passed since last draw (to draw character position animation)
	 */
	virtual void Draw(unsigned int delay = 0);
	virtual void onGetFocus();
	virtual void onLoseFocus();
	virtual bool HandleKeyDown(SDL_Event *sdlEvent, int mod = 0);
	virtual bool HandleKeyUp(SDL_Event *sdlEvent, int mod = 0);
	virtual bool HandleMouseDown(int x, int y, int button);
	virtual bool HandleMouseRelease(int x, int y, int button);

	bool Insert(Uint16 Ch);
	NODE* NewNode(OUT NODE *Front, OUT NODE *Behind, IN LCHAR Ch);
	void GetStringFromNode();

	bool RemoveLeft();
	bool RemoveRight();
	bool MoveLeft();
	bool MoveRight();
	bool MoveStart();
	bool MoveEnd();
	bool CheckPos();
	void FreeString();
	void SelectAll();
	void UnSelectAll();
	int GetCursorX();
	void ClickPos(int x);
	std::string& getText();
};

}

#endif /* __GUI_TEXTINPUT_H */
