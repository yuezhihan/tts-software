//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VoiceWnd.h"
#include "MainWnd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVoiceForm *VoiceForm;
//---------------------------------------------------------------------------
__fastcall TVoiceForm::TVoiceForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVoiceForm::FormCreate(TObject *Sender)
{
	Button1Click(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TVoiceForm::Button1Click(TObject *Sender)
{
	WideString str,C("Microsoft Simplified Chinese"),
        	E1("Microsoft Sam"),E2("Microsoft Mike"),E3("Microsoft Mary");
        int hadC=-1;
	bool hadE=false;
	ListBox1->Clear();
	ISpeechObjectTokensPtr voices=MainForm->speaker->GetVoices(NULL,NULL);
	int count=voices->Count;

        for(int i=0;i<count;++i)
        {
                str=voices->Item(i)->GetDescription(0);
        	ListBox1->Items->Add(str);
                if(str==C) hadC=i;
                if(str==E1 || str==E2 || str==E3) hadE=true;
        }
        if(hadC!=-1 && hadE)
        {
        	ListBox1->ItemIndex=hadC;
        	MainForm->speaker->_set_Voice(MainForm->speaker->GetVoices(NULL,NULL)->Item(hadC));
        }
        else
        {
                bool OK1=false,OK2=false;
        	if(hadC==-1 && (OK1=MessageBox(MainForm->Handle,"�Ҳ���΢�����������⣬�����޷������ʶ���\n\n�����Ƿ���ϵͳΪ���Զ���װ��Լ��10���ӡ�","ѯ�ʣ�",MB_YESNO|MB_ICONQUESTION)==IDYES))
        		WinExec(("msiexec /I "+ExtractFilePath(ParamStr(0))+"database\\΢��tts5.1��������(����).msi").c_str(),SW_SHOWNORMAL);
        	if(!hadE && (OK2=MessageBox(MainForm->Handle,"�Ҳ���΢��Ӣ�������⣬�����޷������ʶ���\n\n�����Ƿ���ϵͳΪ���Զ���װ��Լ��10���ӡ�","ѯ�ʣ�",MB_YESNO|MB_ICONQUESTION)==IDYES))
        		WinExec(("msiexec /I "+ExtractFilePath(ParamStr(0))+"database\\TTS_51_eng.msi").c_str(),SW_SHOWNORMAL);
                if(OK1 || OK2)
                {
                        MessageBox(MainForm->Handle,"��װ��ɺ󵥻�ȷ����ˢ�������⡣","ȷ�ϣ�",MB_OK);
                        Button1Click(NULL);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TVoiceForm::ListBox1Click(TObject *Sender)
{
	MainForm->speaker->_set_Voice(MainForm->speaker->GetVoices(NULL,NULL)->Item(ListBox1->ItemIndex));
}
//---------------------------------------------------------------------------

