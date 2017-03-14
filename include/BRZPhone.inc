/*
	Brazucas'Phone
		textdraws do celular
		tdcelular
			0~25:base
				0~5: fundo
				6~12: moldura
				13~17:capa
				18~20: botoes menu
				21: auto-falante
				22: fundo display
				23: botao chamar
				24~25: botao encerrar
				57: fone
				58: display desligado
			26~37,47~48:discador
				26~34: numeros discador 1~9
				35: +
				36: numeros discador 0
				37: C
				47: salvar
				48: excluir
			38~46:menu
				38: botao discador
				39: botao configuracoes
				40: botao gps
				41: botao saldo bancario
				42: botao sms
				43: botao player
				44: botao agenda
				45: botao registro de chamadas
				46: botao SOS
			49~56:detalhes
				49~51: indicador sinal
				55: hora
				52~54,56: indicador bateria
		tdcelularinterface
			0:display discador
			1:display principal
			2:papel de parede
			3~9:menu de opcoes
*/
#include <a_samp>

#define DIALOG_CONTATO 		83
#define DIALOG_SMS 			84
#define DIALOG_MEU_NUMERO 	85
#define DIALOG_CHAMADA_ESPECIAL 86

#define NENHUM 				0
#define AGENDA 				1
#define CONFIGURACOES 		2
#define TOQUE 				3
#define PAPEL_DE_PAREDE 	4
#define DISCADOR 			5
#define PRINCIPAL 			6
#define SMS 				7
#define INPUT				8
#define ENVIANDO_SMS 		9
#define INIBIDO 			10
#define MEU_NUMERO 			11
#define CHAMADAS 			12
#define CORES 				13
#define GENIUS 				14
#define BANCO 				15
#define GPS 				16
#define CHAMADAS_ESPECIAIS	17
#define GENIUS_DIFICULDADE	18
#define MEDIA_PLAYER		19

new Toques[]={1076,1187,1185,1183,1097,1076,1068,1062,3600};
new Wallpapers[18][0]={"LOADSUK:loadscuk","LOADSUK:loadsc9","LOADSUK:loadsc8","LOADSUK:loadsc7","LOADSUK:loadsc6","LOADSUK:loadsc5","LOADSUK:loadsc4","LOADSUK:loadsc3","LOADSUK:loadsc2","LOADSUK:loadsc14","LOADSUK:loadsc13","LOADSUK:loadsc12","LOADSUK:loadsc11","LOADSUK:loadsc10","LOADSUK:loadsc1","LOADSCS:nvidia","LOADSCS:title_pc_US","load0uk:load0uk"};
new CelularCores[]={0x000000FF,0xFFFFFFFF,0xE837A1FF,0x54AB04FF,0xE0B600FF,0x535355FF,0xF4941CFF,0xFF1C1FFF,0x53379EFF,0x007EB8FF};
new PlayerText:TDCelularInterface[BRAZUCAS_PLAYERS][10];
new PlayerText:TDCelular[BRAZUCAS_PLAYERS][61];
new PlayerText:TDMediaPlayer[BRAZUCAS_PLAYERS][13];
new PlayerText:TDError[BRAZUCAS_PLAYERS][6];

enum celular_info{
	bool:ligado,
	bool:em_chamada,
	bool:inibido,
	bool:ligando,
	bool:em_maos,
	bool:player_tocando,
	papel_de_parede,
	toque,
	cor_celular,
	chamada,
	custo_ligacao
}
new CelularInfo[BRAZUCAS_PLAYERS][celular_info];
//----------------------------------------------------------------------------------------------------------------------------------
new PlayerText:GeniusTD[BRAZUCAS_PLAYERS][9];
new GeniusSons[4]={1084,1056,1057,1058};
enum genius_info{
	bool:jogando,
	jogada,
	pontos_conseguidos,
	sequencia,
	piscadas,
	jogada_esperada[20],
	jogada_realizada[20],
	dificuldade
}
new Genius[BRAZUCAS_PLAYERS][genius_info];
//----------------------------------------------------------------------------------------------------------------------------------
stock CarregarCelular(playerid)
{
	if(fexist(Celular(playerid)))
	{
		CelularInfo[playerid][papel_de_parede]=dini_Int(Celular(playerid),"wallpaper");
		CelularInfo[playerid][toque]=dini_Int(Celular(playerid),"toque");
		CelularInfo[playerid][ligado]=(dini_Int(Celular(playerid),"ligado")==1)?(true):(false);	
		CelularInfo[playerid][inibido]=(dini_Int(Celular(playerid),"inibido")==1)?(true):(false);
		CelularInfo[playerid][cor_celular]=dini_Int(Celular(playerid),"cor");	
	}
	AtualizarCor(playerid,CelularInfo[playerid][cor_celular],false);
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][2],Wallpapers[CelularInfo[playerid][papel_de_parede]]);
}
//----------------------------------------------------------------------------------------------------------------------------------
stock CriarAparelho(p)
{
	//Base do celular (Moldura)
	TDCelular[p][0] = CreatePlayerTextDraw(p,437.000000, 272.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][0], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][0], 255);
	PlayerTextDrawFont(p,TDCelular[p][0], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][0], 0.500000, 18.100009);
	PlayerTextDrawColor(p,TDCelular[p][0], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][0], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][0], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][0], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][0], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][0], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][0], 4.000000, 73.000000);

	TDCelular[p][1] = CreatePlayerTextDraw(p,437.000000, 264.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][1], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][1], 255);
	PlayerTextDrawFont(p,TDCelular[p][1], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][1], 0.500000, 20.000017);
	PlayerTextDrawColor(p,TDCelular[p][1], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][1], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][1], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][1], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][1], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][1], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][1], 4.000000, 62.000000);

	TDCelular[p][2] = CreatePlayerTextDraw(p,399.000000, 249.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][2], 255);
	PlayerTextDrawFont(p,TDCelular[p][2], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][2], 0.649999, 3.900000);
	PlayerTextDrawColor(p,TDCelular[p][2], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][2], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][2], 1);

	TDCelular[p][3] = CreatePlayerTextDraw(p,462.000000, 249.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][3], 255);
	PlayerTextDrawFont(p,TDCelular[p][3], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][3], 0.649999, 3.900000);
	PlayerTextDrawColor(p,TDCelular[p][3], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][3], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][3], 1);

	TDCelular[p][4] = CreatePlayerTextDraw(p,462.000000, 415.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][4], 255);
	PlayerTextDrawFont(p,TDCelular[p][4], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][4], 0.649999, 3.900000);
	PlayerTextDrawColor(p,TDCelular[p][4], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][4], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][4], 1);

	TDCelular[p][5] = CreatePlayerTextDraw(p,399.000000, 421.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][5], 255);
	PlayerTextDrawFont(p,TDCelular[p][5], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][5], 0.539999, 3.099998);
	PlayerTextDrawColor(p,TDCelular[p][5], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][5], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][5], 1);

	TDCelular[p][6] = CreatePlayerTextDraw(p,437.000000, 274.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][6], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][6], 255);
	PlayerTextDrawFont(p,TDCelular[p][6], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][6], 0.500000, 18.000009);
	PlayerTextDrawColor(p,TDCelular[p][6], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][6], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][6], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][6], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][6], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][6], -757935361);
	PlayerTextDrawTextSize(p,TDCelular[p][6], 4.000000, 71.000000);

	TDCelular[p][7] = CreatePlayerTextDraw(p,437.000000, 266.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][7], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][7], 255);
	PlayerTextDrawFont(p,TDCelular[p][7], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][7], 0.500000, 19.600015);
	PlayerTextDrawColor(p,TDCelular[p][7], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][7], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][7], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][7], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][7], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][7], -757935361);
	PlayerTextDrawTextSize(p,TDCelular[p][7], 4.000000, 62.000000);

	TDCelular[p][8] = CreatePlayerTextDraw(p,400.000000, 250.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][8], -757935361);
	PlayerTextDrawFont(p,TDCelular[p][8], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][8], 0.649999, 3.900000);
	PlayerTextDrawColor(p,TDCelular[p][8], -757935361);
	PlayerTextDrawSetOutline(p,TDCelular[p][8], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][8], 1);

	TDCelular[p][9] = CreatePlayerTextDraw(p,461.000000, 250.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][9], -757935361);
	PlayerTextDrawFont(p,TDCelular[p][9], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][9], 0.649999, 3.900000);
	PlayerTextDrawColor(p,TDCelular[p][9], -757935361);
	PlayerTextDrawSetOutline(p,TDCelular[p][9], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][9], 1);

	TDCelular[p][10] = CreatePlayerTextDraw(p,461.000000, 413.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][10], -757935361);
	PlayerTextDrawFont(p,TDCelular[p][10], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][10], 0.649999, 3.900000);
	PlayerTextDrawColor(p,TDCelular[p][10], -757935361);
	PlayerTextDrawSetOutline(p,TDCelular[p][10], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][10], 1);

	TDCelular[p][11] = CreatePlayerTextDraw(p,400.000000, 419.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][11], -757935361);
	PlayerTextDrawFont(p,TDCelular[p][11], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][11], 0.539999, 3.099998);
	PlayerTextDrawColor(p,TDCelular[p][11], -757935361);
	PlayerTextDrawSetOutline(p,TDCelular[p][11], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][11], 1);

	TDCelular[p][12] = CreatePlayerTextDraw(p,402.000000, 423.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][12], 255);
	PlayerTextDrawFont(p,TDCelular[p][12], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][12], 0.509999, 2.400000);
	PlayerTextDrawColor(p,TDCelular[p][12], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][12], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][12], 1);

	TDCelular[p][13] = CreatePlayerTextDraw(p,437.000000, 267.899993, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][13], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][13], 255);
	PlayerTextDrawFont(p,TDCelular[p][13], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][13], 0.449900, 19.149999);
	PlayerTextDrawColor(p,TDCelular[p][13], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][13], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][13], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][13], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][13], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][13], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][13], 0.000000, 59.000000);

	TDCelular[p][14] = CreatePlayerTextDraw(p,437.000000, 274.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][14], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][14], 255);
	PlayerTextDrawFont(p,TDCelular[p][14], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][14], 0.500000, 17.800008);
	PlayerTextDrawColor(p,TDCelular[p][14], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][14], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][14], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][14], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][14], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][14], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][14], -4.000000, 68.000000);

	TDCelular[p][15] = CreatePlayerTextDraw(p,462.500000, 423.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][15], 255);
	PlayerTextDrawFont(p,TDCelular[p][15], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][15], 0.509999, 2.400000);
	PlayerTextDrawColor(p,TDCelular[p][15], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][15], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][15], 1);

	TDCelular[p][16] = CreatePlayerTextDraw(p,462.500000, 258.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][16], 255);
	PlayerTextDrawFont(p,TDCelular[p][16], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][16], 0.509999, 2.400000);
	PlayerTextDrawColor(p,TDCelular[p][16], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][16], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][16], 1);

	TDCelular[p][17] = CreatePlayerTextDraw(p,402.000000, 258.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][17], 255);
	PlayerTextDrawFont(p,TDCelular[p][17], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][17], 0.509999, 2.400000);
	PlayerTextDrawColor(p,TDCelular[p][17], 255);
	PlayerTextDrawSetOutline(p,TDCelular[p][17], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][17], 1);

	TDCelular[p][18] = CreatePlayerTextDraw(p,427.000000, 406.000000, "O");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][18], 168430335);
	PlayerTextDrawFont(p,TDCelular[p][18], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][18], 0.720000, 3.399997);
	PlayerTextDrawColor(p,TDCelular[p][18], 168430335);
	PlayerTextDrawSetOutline(p,TDCelular[p][18], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][18], 1);
	PlayerTextDrawSetSelectable(p,TDCelular[p][18],1);

	TDCelular[p][19] = CreatePlayerTextDraw(p,434.000000, 416.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][19], 168430335);
	PlayerTextDrawFont(p,TDCelular[p][19], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][19], 0.259999, 1.399997);
	PlayerTextDrawColor(p,TDCelular[p][19], -255);
	PlayerTextDrawSetOutline(p,TDCelular[p][19], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][19], 1);
	PlayerTextDrawSetSelectable(p,TDCelular[p][19],1);

	TDCelular[p][20] = CreatePlayerTextDraw(p,432.000000, 412.000000, "O");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][20], 168430335);
	PlayerTextDrawFont(p,TDCelular[p][20], 2);
	PlayerTextDrawLetterSize(p,TDCelular[p][20], 0.340000, 2.099999);
	PlayerTextDrawColor(p,TDCelular[p][20], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][20], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][20], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][20], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][20], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][20], -256);
	PlayerTextDrawTextSize(p,TDCelular[p][20], 442.000000, -50.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][20],1);

	TDCelular[p][21] = CreatePlayerTextDraw(p,428.000000, 272.000000, "O");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][21], 168430335);
	PlayerTextDrawFont(p,TDCelular[p][21], 2);
	PlayerTextDrawLetterSize(p,TDCelular[p][21], 0.639999, 0.800001);
	PlayerTextDrawColor(p,TDCelular[p][21], 168430335);
	PlayerTextDrawSetOutline(p,TDCelular[p][21], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][21], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][21], 0);

	TDCelular[p][22] = CreatePlayerTextDraw(p,437.000000, 287.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][22], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][22], 255);
	PlayerTextDrawFont(p,TDCelular[p][22], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][22], 0.280000, 12.800006);
	PlayerTextDrawColor(p,TDCelular[p][22], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][22], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][22], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][22], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][22], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][22], -926365441);
	PlayerTextDrawTextSize(p,TDCelular[p][22], 1.000000, 59.000000);

	TDCelular[p][23] = CreatePlayerTextDraw(p,415.000000, 407.000000, "(");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][23], 255);
	PlayerTextDrawFont(p,TDCelular[p][23], 2);
	PlayerTextDrawLetterSize(p,TDCelular[p][23], 0.389999, 3.099998);
	PlayerTextDrawColor(p,TDCelular[p][23], 8388863);
	PlayerTextDrawSetOutline(p,TDCelular[p][23], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][23], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][23], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][23], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][23], -256);
	PlayerTextDrawTextSize(p,TDCelular[p][23], 421.000000, 30.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][23],1);
	
	TDCelular[p][24] = CreatePlayerTextDraw(p,454.000000, 412.000000, "'");
	PlayerTextDrawAlignment(p,TDCelular[p][24], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][24], 255);
	PlayerTextDrawFont(p,TDCelular[p][24], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][24], 0.150000, 4.099998);
	PlayerTextDrawColor(p,TDCelular[p][24], -16776961);
	PlayerTextDrawSetOutline(p,TDCelular[p][24], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][24], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][24], 0);

	TDCelular[p][25] = CreatePlayerTextDraw(p,453.000000, 407.000000, ")");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][25], 255);
	PlayerTextDrawFont(p,TDCelular[p][25], 2);
	PlayerTextDrawLetterSize(p,TDCelular[p][25], 0.389999, 3.099997);
	PlayerTextDrawColor(p,TDCelular[p][25], -16776961);
	PlayerTextDrawSetOutline(p,TDCelular[p][25], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][25], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][25], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][25], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][25], -256);
	PlayerTextDrawTextSize(p,TDCelular[p][25], 460.000000, 30.000000);	
	PlayerTextDrawSetSelectable(p,TDCelular[p][25],1);
	
	TDCelular[p][59] = CreatePlayerTextDraw(p,408.000000, 287.500000, "_");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][59], 255);
	PlayerTextDrawFont(p,TDCelular[p][59], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][59], 0.190000, 0.800000);
	PlayerTextDrawColor(p,TDCelular[p][59], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][59], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][59], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][59], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][59], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][59], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][59], 466.000000, 0.000000);

	TDCelular[p][60] = CreatePlayerTextDraw(p,408.000000, 287.500000, "_");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][60], 255);
	PlayerTextDrawFont(p,TDCelular[p][60], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][60], 0.27, 0.20);
	PlayerTextDrawColor(p,TDCelular[p][60], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][60], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][60], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][60], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][60], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][60], -251);
	PlayerTextDrawTextSize(p,TDCelular[p][60], 466.000000, 0.000000);
	
	TDCelular[p][57] = CreatePlayerTextDraw(p,437.000000, 267.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][57], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][57], 255);
	PlayerTextDrawFont(p,TDCelular[p][57], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][57], 0.500000, 10.000017);
	PlayerTextDrawColor(p,TDCelular[p][57], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][57], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][57], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][57], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][57], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][57], -251);
	PlayerTextDrawTextSize(p,TDCelular[p][57], 4.000000, 69.000000);	
	
	TDCelular[p][58] = CreatePlayerTextDraw(p,437.000000, 287.000000, "_");
	PlayerTextDrawAlignment(p,TDCelular[p][58], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][58], 255);
	PlayerTextDrawFont(p,TDCelular[p][58], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][58], 0.280000, 12.800006);
	PlayerTextDrawColor(p,TDCelular[p][58], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][58], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][58], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][58], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][58], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][58], 200);
	PlayerTextDrawTextSize(p,TDCelular[p][58], 1.000000, 59.000000);
	
	//display discador
	TDCelularInterface[p][0] = CreatePlayerTextDraw(p,467.000000, 295.000000, "999999999"); 
	PlayerTextDrawAlignment(p,TDCelularInterface[p][0], 3);
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][0], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][0], 1);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][0], 0.300000, 2.200001);
	PlayerTextDrawColor(p,TDCelularInterface[p][0], 255);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][0], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][0], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][0], 0);
		
	//display principal
	TDCelularInterface[p][1] = CreatePlayerTextDraw(p,408.000000, 299.000000, "_~n~_~n~_~n~_~n~_~n~_~n~_~n~_~n~_~n~_~n~_~n~_");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][1], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][1], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][1], 0.119999, 0.949999);
	PlayerTextDrawColor(p,TDCelularInterface[p][1], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][1], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][1], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][1], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][1], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][1], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][1], 466.000000, 10.000000);
		
	//wallpaper
	TDCelularInterface[p][2] = CreatePlayerTextDraw(p,406.000000, 296.000000, "load0uk:load0uk");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][2], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][2], 4);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][2], 0.119999, 0.949999);
	PlayerTextDrawColor(p,TDCelularInterface[p][2], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][2], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][2], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][2], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][2], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][2], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][2], 62.000000, 108.000000);	

	TDCelular[p][49] = CreatePlayerTextDraw(p,408.000000, 289.000000, "l");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][49], 255);
	PlayerTextDrawFont(p,TDCelular[p][49], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][49], 0.310000, 0.699998);
	PlayerTextDrawColor(p,TDCelular[p][49], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][49], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][49], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][49], 1);

	TDCelular[p][50] = CreatePlayerTextDraw(p,410.000000, 286.500000, "l");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][50], 255);
	PlayerTextDrawFont(p,TDCelular[p][50], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][50], 0.310000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][50], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][50], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][50], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][50], 1);

	TDCelular[p][51] = CreatePlayerTextDraw(p,412.000000, 284.500000, "l");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][51], 255);
	PlayerTextDrawFont(p,TDCelular[p][51], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][51], 0.310000, 1.250000);
	PlayerTextDrawColor(p,TDCelular[p][51], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][51], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][51], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][51], 1);

	TDCelular[p][52] = CreatePlayerTextDraw(p,457.000000, 289.500000, "_");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][52], 255);
	PlayerTextDrawFont(p,TDCelular[p][52], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][52], 0.500000, 0.200000);
	PlayerTextDrawColor(p,TDCelular[p][52], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][52], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][52], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][52], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][52], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][52], -1);
	PlayerTextDrawTextSize(p,TDCelular[p][52], 462.000000, 3.000000);

	TDCelular[p][53] = CreatePlayerTextDraw(p,458.000000, 291.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][53], 255);
	PlayerTextDrawFont(p,TDCelular[p][53], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][53], 0.500000, -0.100000);
	PlayerTextDrawColor(p,TDCelular[p][53], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][53], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][53], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][53], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][53], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][53], -1);
	PlayerTextDrawTextSize(p,TDCelular[p][53], 463.000000, 3.000000);

	TDCelular[p][54] = CreatePlayerTextDraw(p,458.000000, 291.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][54], 255);
	PlayerTextDrawFont(p,TDCelular[p][54], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][54], 0.500000, -0.100000);
	PlayerTextDrawColor(p,TDCelular[p][54], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][54], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][54], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][54], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][54], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][54], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][54], 461.000000, 3.000000);
				
	//menu de opcoes
	TDCelularInterface[p][3] = CreatePlayerTextDraw(p,408.000000, 299.500000, "Opcao1");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][3], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][3], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][3], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][3], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][3], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][3], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][3], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][3], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][3], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][3], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][3],1);	

	TDCelularInterface[p][4] = CreatePlayerTextDraw(p,408.000000, 314.500000, "Opcao2");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][4], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][4], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][4], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][4], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][4], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][4], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][4], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][4], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][4], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][4], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][4],1);	

	TDCelularInterface[p][5] = CreatePlayerTextDraw(p,408.000000, 330.000000, "opcao3");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][5], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][5], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][5], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][5], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][5], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][5], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][5], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][5], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][5], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][5], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][5],1);	

	TDCelularInterface[p][6] = CreatePlayerTextDraw(p,408.000000, 345.000000, "opcao4");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][6], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][6], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][6], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][6], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][6], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][6], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][6], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][6], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][6], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][6], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][6],1);	

	TDCelularInterface[p][7] = CreatePlayerTextDraw(p,408.000000, 360.000000, "opcao5");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][7], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][7], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][7], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][7], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][7], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][7], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][7], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][7], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][7], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][7], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][7],1);	

	TDCelularInterface[p][8] = CreatePlayerTextDraw(p,408.000000, 375.500000, "opcao6");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][8], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][8], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][8], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][8], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][8], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][8], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][8], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][8], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][8], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][8], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][8],1);	

	TDCelularInterface[p][9] = CreatePlayerTextDraw(p,408.000000, 391.000000, "opcao7");
	PlayerTextDrawBackgroundColor(p,TDCelularInterface[p][9], 255);
	PlayerTextDrawFont(p,TDCelularInterface[p][9], 2);
	PlayerTextDrawLetterSize(p,TDCelularInterface[p][9], 0.119998, 0.949998);
	PlayerTextDrawColor(p,TDCelularInterface[p][9], -1);
	PlayerTextDrawSetOutline(p,TDCelularInterface[p][9], 0);
	PlayerTextDrawSetProportional(p,TDCelularInterface[p][9], 1);
	PlayerTextDrawSetShadow(p,TDCelularInterface[p][9], 0);
	PlayerTextDrawUseBox(p,TDCelularInterface[p][9], 1);
	PlayerTextDrawBoxColor(p,TDCelularInterface[p][9], 1394868);
	PlayerTextDrawTextSize(p,TDCelularInterface[p][9], 466.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelularInterface[p][9],1);
	
	//Discador do celular
	TDCelular[p][26] = CreatePlayerTextDraw(p,416.000000, 324.000000, "1");
	PlayerTextDrawAlignment(p,TDCelular[p][26], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][26], 255);
	PlayerTextDrawFont(p,TDCelular[p][26], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][26], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][26], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][26], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][26], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][26], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][26], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][26], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][26], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][26],1);

	TDCelular[p][27] = CreatePlayerTextDraw(p,437.000000, 324.000000, "2");
	PlayerTextDrawAlignment(p,TDCelular[p][27], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][27], 255);
	PlayerTextDrawFont(p,TDCelular[p][27], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][27], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][27], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][27], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][27], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][27], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][27], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][27], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][27], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][27],1);

	TDCelular[p][28] = CreatePlayerTextDraw(p,458.000000, 324.000000, "3");
	PlayerTextDrawAlignment(p,TDCelular[p][28], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][28], 255);
	PlayerTextDrawFont(p,TDCelular[p][28], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][28], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][28], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][28], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][28], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][28], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][28], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][28], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][28], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][28],1);

	TDCelular[p][29] = CreatePlayerTextDraw(p,416.000000, 345.000000, "4");
	PlayerTextDrawAlignment(p,TDCelular[p][29], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][29], 255);
	PlayerTextDrawFont(p,TDCelular[p][29], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][29], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][29], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][29], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][29], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][29], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][29], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][29], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][29], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][29],1);

	TDCelular[p][30] = CreatePlayerTextDraw(p,437.000000, 345.000000, "5");
	PlayerTextDrawAlignment(p,TDCelular[p][30], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][30], 255);
	PlayerTextDrawFont(p,TDCelular[p][30], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][30], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][30], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][30], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][30], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][30], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][30], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][30], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][30], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][30],1);

	TDCelular[p][31] = CreatePlayerTextDraw(p,458.000000, 345.000000, "6");
	PlayerTextDrawAlignment(p,TDCelular[p][31], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][31], 255);
	PlayerTextDrawFont(p,TDCelular[p][31], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][31], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][31], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][31], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][31], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][31], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][31], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][31], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][31], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][31],1);

	TDCelular[p][32] = CreatePlayerTextDraw(p,416.000000, 366.000000, "7");
	PlayerTextDrawAlignment(p,TDCelular[p][32], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][32], 255);
	PlayerTextDrawFont(p,TDCelular[p][32], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][32], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][32], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][32], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][32], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][32], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][32], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][32], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][32], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][32],1);

	TDCelular[p][33] = CreatePlayerTextDraw(p,437.000000, 366.000000, "8");
	PlayerTextDrawAlignment(p,TDCelular[p][33], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][33], 255);
	PlayerTextDrawFont(p,TDCelular[p][33], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][33], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][33], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][33], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][33], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][33], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][33], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][33], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][33], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][33],1);

	TDCelular[p][34] = CreatePlayerTextDraw(p,458.000000, 366.000000, "9");
	PlayerTextDrawAlignment(p,TDCelular[p][34], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][34], 255);
	PlayerTextDrawFont(p,TDCelular[p][34], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][34], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][34], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][34], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][34], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][34], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][34], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][34], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][34], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][34],1);

	TDCelular[p][35] = CreatePlayerTextDraw(p,416.000000, 387.000000, "M");
	PlayerTextDrawAlignment(p,TDCelular[p][35], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][35], 255);
	PlayerTextDrawFont(p,TDCelular[p][35], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][35], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][35], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][35], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][35], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][35], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][35], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][35], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][35], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][35],1);

	TDCelular[p][36] = CreatePlayerTextDraw(p,437.000000, 387.000000, "0");
	PlayerTextDrawAlignment(p,TDCelular[p][36], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][36], 255);
	PlayerTextDrawFont(p,TDCelular[p][36], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][36], 0.209999, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][36], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][36], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][36], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][36], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][36], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][36], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][36], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][36],1);

	TDCelular[p][37] = CreatePlayerTextDraw(p,458.000000, 387.000000, "C");
	PlayerTextDrawAlignment(p,TDCelular[p][37], 2);
	PlayerTextDrawBackgroundColor(p,TDCelular[p][37], 255);
	PlayerTextDrawFont(p,TDCelular[p][37], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][37], 0.209998, 1.549998);
	PlayerTextDrawColor(p,TDCelular[p][37], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][37], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][37], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][37], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][37], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][37], 1394868);
	PlayerTextDrawTextSize(p,TDCelular[p][37], 10.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][37],1);
	
	//Menu do celular
	TDCelular[p][38] = CreatePlayerTextDraw(p,408.000000, 305.000000, "#");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][38], 255);
	PlayerTextDrawFont(p,TDCelular[p][38], 1);
	PlayerTextDrawLetterSize(p,TDCelular[p][38], 0.799998, 3.299998);
	PlayerTextDrawColor(p,TDCelular[p][38], 6068460);
	PlayerTextDrawSetOutline(p,TDCelular[p][38], 1);
	PlayerTextDrawSetProportional(p,TDCelular[p][38], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][38], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][38], -256);
	PlayerTextDrawTextSize(p,TDCelular[p][38], 426.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][38],1);	

	TDCelular[p][39] = CreatePlayerTextDraw(p,428.000000, 310.000000, "hud:radar_modGarage");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][39], 255);
	PlayerTextDrawFont(p,TDCelular[p][39], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][39], 0.960000, 5.000000);
	PlayerTextDrawColor(p,TDCelular[p][39], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][39], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][39], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][39], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][39], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][39], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][39], 16.000000, 22.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][39],1);	

	TDCelular[p][40] = CreatePlayerTextDraw(p,447.000000, 304.000000, "hud:radar_impound");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][40], 255);
	PlayerTextDrawFont(p,TDCelular[p][40], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][40], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][40], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][40], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][40], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][40], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][40], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][40], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][40], 19.000000, 27.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][40],1);	

	TDCelular[p][41] = CreatePlayerTextDraw(p,409.000000, 339.000000, "hud:radar_cash");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][41], 255);
	PlayerTextDrawFont(p,TDCelular[p][41], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][41], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][41], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][41], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][41], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][41], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][41], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][41], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][41], 17.000000, 22.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][41],1);	

	TDCelular[p][42] = CreatePlayerTextDraw(p,429.000000, 339.000000, "LD_CHAT:thumbup");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][42], 255);
	PlayerTextDrawFont(p,TDCelular[p][42], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][42], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][42], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][42], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][42], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][42], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][42], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][42], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][42], 15.000000, 22.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][42],1);	

	TDCelular[p][43] = CreatePlayerTextDraw(p,448.000000, 339.000000, "hud:radar_dateDisco");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][43], 255);
	PlayerTextDrawFont(p,TDCelular[p][43], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][43], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][43], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][43], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][43], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][43], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][43], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][43], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][43], 17.000000, 23.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][43],1);	

	TDCelular[p][44] = CreatePlayerTextDraw(p,410.000000, 371.000000, "hud:radar_saveGame");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][44], 255);
	PlayerTextDrawFont(p,TDCelular[p][44], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][44], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][44], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][44], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][44], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][44], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][44], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][44], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][44], 16.000000, 20.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][44],1);	

	TDCelular[p][45] = CreatePlayerTextDraw(p,429.000000, 369.000000, "LD_CHAT:goodcha");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][45], 255);
	PlayerTextDrawFont(p,TDCelular[p][45], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][45], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][45], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][45], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][45], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][45], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][45], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][45], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][45], 17.000000, 22.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][45],1);	

	TDCelular[p][46] = CreatePlayerTextDraw(p,449.000000, 371.000000, "hud:radar_mafiaCasino");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][46], 255);
	PlayerTextDrawFont(p,TDCelular[p][46], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][46], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][46], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][46], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][46], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][46], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][46], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][46], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][46], 16.000000, 20.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][46],1);	
	
	TDCelular[p][47] = CreatePlayerTextDraw(p,406.000000, 313.000000, "salvar");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][47], 255);
	PlayerTextDrawFont(p,TDCelular[p][47], 2);
	PlayerTextDrawLetterSize(p,TDCelular[p][47], 0.119999, 0.799999);
	PlayerTextDrawColor(p,TDCelular[p][47], 945528830);
	PlayerTextDrawSetOutline(p,TDCelular[p][47], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][47], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][47], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][47], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][47], 945528576);
	PlayerTextDrawTextSize(p,TDCelular[p][47], 425.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][47],1);	

	TDCelular[p][48] = CreatePlayerTextDraw(p,448.000000, 313.000000, "excluir");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][48], 255);
	PlayerTextDrawFont(p,TDCelular[p][48], 2);
	PlayerTextDrawLetterSize(p,TDCelular[p][48], 0.119999, 0.799999);
	PlayerTextDrawColor(p,TDCelular[p][48], 945528830);
	PlayerTextDrawSetOutline(p,TDCelular[p][48], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][48], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][48], 0);
	PlayerTextDrawUseBox(p,TDCelular[p][48], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][48], 945528576);
	PlayerTextDrawTextSize(p,TDCelular[p][48], 460.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][48],1);
	
	TDCelular[p][55] = CreatePlayerTextDraw(p,418.000000, 285.500000, "hud:radar_enemyAttack");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][55], 255);
	PlayerTextDrawFont(p,TDCelular[p][55], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][55], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][55], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][55], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][55], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][55], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][55], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][55], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][55], 8.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][55],1);

	TDCelular[p][56] = CreatePlayerTextDraw(p,427.000000, 285.500000, "LD_CHAT:badchat");
	PlayerTextDrawBackgroundColor(p,TDCelular[p][56], 255);
	PlayerTextDrawFont(p,TDCelular[p][56], 4);
	PlayerTextDrawLetterSize(p,TDCelular[p][56], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDCelular[p][56], -1);
	PlayerTextDrawSetOutline(p,TDCelular[p][56], 0);
	PlayerTextDrawSetProportional(p,TDCelular[p][56], 1);
	PlayerTextDrawSetShadow(p,TDCelular[p][56], 1);
	PlayerTextDrawUseBox(p,TDCelular[p][56], 1);
	PlayerTextDrawBoxColor(p,TDCelular[p][56], 255);
	PlayerTextDrawTextSize(p,TDCelular[p][56], 8.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDCelular[p][56],1);
	
	//media player
	
	TDMediaPlayer[p][0] = CreatePlayerTextDraw(p,437.000000, 299.000000, "_");
	PlayerTextDrawAlignment(p,TDMediaPlayer[p][0], 2);
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][0], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][0], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][0], 0.500000, 11.400000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][0], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][0], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][0], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][0], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][0], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][0], 0xFFFFFF22);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][0], -1.000000, 58.000000);

	TDMediaPlayer[p][1] = CreatePlayerTextDraw(p,437.000000, 304.000000, "Radio");
	PlayerTextDrawAlignment(p,TDMediaPlayer[p][1], 2);
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][1], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][1], 2);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][1], 0.119999, 0.799998);
	PlayerTextDrawColor(p,TDMediaPlayer[p][1], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][1], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][1], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][1], 0);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][1], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][1], 234);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][1], 464.000000, 54.000000);

	TDMediaPlayer[p][2] = CreatePlayerTextDraw(p,410.000000, 375.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][2], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][2], 2);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][2], 0.119999, 2.099998);
	PlayerTextDrawColor(p,TDMediaPlayer[p][2], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][2], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][2], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][2], 0);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][2], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][2], 234);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][2], 464.000000, 0.000000);

	TDMediaPlayer[p][3] = CreatePlayerTextDraw(p,418.000000, 360.000000, "LD_BEAT:chit");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][3], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][3], 4);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][3], 0.440000, 0.699999);
	PlayerTextDrawColor(p,TDMediaPlayer[p][3], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][3], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][3], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][3], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][3], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][3], 255);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][3], 38.000000, 49.000000);

	TDMediaPlayer[p][4] = CreatePlayerTextDraw(p,430.000000, 370.000000, "~>~");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][4], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][4], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][4], 0.920000, 2.700000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][4], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][4], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][4], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][4], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][4], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][4], 0);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][4], 444.000000, 20.000000);
	PlayerTextDrawSetSelectable(p,TDMediaPlayer[p][4],1);

	TDMediaPlayer[p][5] = CreatePlayerTextDraw(p,430.000000, 370.000000, "ll");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][5], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][5], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][5], 0.719999, 2.899999);
	PlayerTextDrawColor(p,TDMediaPlayer[p][5], 1852731135);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][5], 1);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][5], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][5], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][5], 0);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][5], 444.000000, 20.000000);
	PlayerTextDrawSetSelectable(p,TDMediaPlayer[p][5],1);

	TDMediaPlayer[p][6] = CreatePlayerTextDraw(p,414.000000, 377.000000, "~<~");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][6], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][6], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][6], 0.569999, 1.500000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][6], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][6], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][6], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][6], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][6], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][6], 0);	

	TDMediaPlayer[p][7] = CreatePlayerTextDraw(p,410.000000, 377.000000, "~<~");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][7], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][7], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][7], 0.569999, 1.500000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][7], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][7], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][7], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][7], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][7], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][7], 0);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][7], 422.000000, 20.000000);
	PlayerTextDrawSetSelectable(p,TDMediaPlayer[p][7],1);

	TDMediaPlayer[p][8] = CreatePlayerTextDraw(p,452.000000, 377.000000, "~>~");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][8], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][8], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][8], 0.569999, 1.500000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][8], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][8], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][8], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][8], 1);

	TDMediaPlayer[p][9] = CreatePlayerTextDraw(p,456.000000, 377.000000, "~>~");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][9], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][9], 1);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][9], 0.569999, 1.500000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][9], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][9], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][9], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][9], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][9], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][9], 0);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][9], 463.000000, 20.000000);
	PlayerTextDrawSetSelectable(p,TDMediaPlayer[p][9],1);

	TDMediaPlayer[p][10] = CreatePlayerTextDraw(p,410.000000, 304.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][10], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][10], 2);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][10], 0.119999, 0.099998);
	PlayerTextDrawColor(p,TDMediaPlayer[p][10], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][10], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][10], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][10], 0);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][10], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][10], -244);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][10], 464.000000, 3.000000);

	TDMediaPlayer[p][11] = CreatePlayerTextDraw(p,410.000000, 375.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][11], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][11], 2);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][11], 0.119999, 0.799998);
	PlayerTextDrawColor(p,TDMediaPlayer[p][11], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][11], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][11], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][11], 0);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][11], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][11], -244);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][11], 464.000000, 0.000000);

	TDMediaPlayer[p][12] = CreatePlayerTextDraw(p,410.000000, 320.000000, "Brazucas'Radio");
	PlayerTextDrawBackgroundColor(p,TDMediaPlayer[p][12], 255);
	PlayerTextDrawFont(p,TDMediaPlayer[p][12], 2);
	PlayerTextDrawLetterSize(p,TDMediaPlayer[p][12], 0.120000, 0.800000);
	PlayerTextDrawColor(p,TDMediaPlayer[p][12], -1);
	PlayerTextDrawSetOutline(p,TDMediaPlayer[p][12], 0);
	PlayerTextDrawSetProportional(p,TDMediaPlayer[p][12], 1);
	PlayerTextDrawSetShadow(p,TDMediaPlayer[p][12], 1);
	PlayerTextDrawUseBox(p,TDMediaPlayer[p][12], 1);
	PlayerTextDrawBoxColor(p,TDMediaPlayer[p][12], 0);
	PlayerTextDrawTextSize(p,TDMediaPlayer[p][12], 464.000000, 62.000000);
	
	CriarGeniusTD(p);
	
	TDError[p][0] = CreatePlayerTextDraw(p,410.000000, 344.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDError[p][0], 255);
	PlayerTextDrawFont(p,TDError[p][0], 1);
	PlayerTextDrawLetterSize(p,TDError[p][0], 0.500000, 6.000000);
	PlayerTextDrawColor(p,TDError[p][0], -1);
	PlayerTextDrawSetOutline(p,TDError[p][0], 0);
	PlayerTextDrawSetProportional(p,TDError[p][0], 1);
	PlayerTextDrawSetShadow(p,TDError[p][0], 1);
	PlayerTextDrawUseBox(p,TDError[p][0], 1);
	PlayerTextDrawBoxColor(p,TDError[p][0], 255);
	PlayerTextDrawTextSize(p,TDError[p][0], 463.000000, 30.000000);

	TDError[p][1] = CreatePlayerTextDraw(p,411.000000, 355.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDError[p][1], 255);
	PlayerTextDrawFont(p,TDError[p][1], 1);
	PlayerTextDrawLetterSize(p,TDError[p][1], 0.500000, 4.600001);
	PlayerTextDrawColor(p,TDError[p][1], -1);
	PlayerTextDrawSetOutline(p,TDError[p][1], 0);
	PlayerTextDrawSetProportional(p,TDError[p][1], 1);
	PlayerTextDrawSetShadow(p,TDError[p][1], 1);
	PlayerTextDrawUseBox(p,TDError[p][1], 1);
	PlayerTextDrawBoxColor(p,TDError[p][1], -1);
	PlayerTextDrawTextSize(p,TDError[p][1], 462.000000, 30.000000);

	TDError[p][2] = CreatePlayerTextDraw(p,409.000000, 342.000000, "Erro");
	PlayerTextDrawBackgroundColor(p,TDError[p][2], 255);
	PlayerTextDrawFont(p,TDError[p][2], 1);
	PlayerTextDrawLetterSize(p,TDError[p][2], 0.250000, 1.000000);
	PlayerTextDrawColor(p,TDError[p][2], -1);
	PlayerTextDrawSetOutline(p,TDError[p][2], 0);
	PlayerTextDrawSetProportional(p,TDError[p][2], 1);
	PlayerTextDrawSetShadow(p,TDError[p][2], 1);

	TDError[p][3] = CreatePlayerTextDraw(p,411.000000, 355.000000, "Mensagem de erro");
	PlayerTextDrawBackgroundColor(p,TDError[p][3], 255);
	PlayerTextDrawFont(p,TDError[p][3], 1);
	PlayerTextDrawLetterSize(p,TDError[p][3], 0.170000, 0.799999);
	PlayerTextDrawColor(p,TDError[p][3], 255);
	PlayerTextDrawSetOutline(p,TDError[p][3], 0);
	PlayerTextDrawSetProportional(p,TDError[p][3], 1);
	PlayerTextDrawSetShadow(p,TDError[p][3], 0);
	PlayerTextDrawUseBox(p,TDError[p][3], 1);
	PlayerTextDrawBoxColor(p,TDError[p][3], -256);
	PlayerTextDrawTextSize(p,TDError[p][3], 462.000000, 30.000000);

	TDError[p][4] = CreatePlayerTextDraw(p,415.000000, 381.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDError[p][4], 255);
	PlayerTextDrawFont(p,TDError[p][4], 1);
	PlayerTextDrawLetterSize(p,TDError[p][4], 0.500000, 1.400000);
	PlayerTextDrawColor(p,TDError[p][4], -1);
	PlayerTextDrawSetOutline(p,TDError[p][4], 0);
	PlayerTextDrawSetProportional(p,TDError[p][4], 1);
	PlayerTextDrawSetShadow(p,TDError[p][4], 1);
	PlayerTextDrawUseBox(p,TDError[p][4], 1);
	PlayerTextDrawBoxColor(p,TDError[p][4], 255);
	PlayerTextDrawTextSize(p,TDError[p][4], 458.000000, 30.000000);

	TDError[p][5] = CreatePlayerTextDraw(p,436.000000, 382.000000, "Ok");
	PlayerTextDrawAlignment(p,TDError[p][5], 2);
	PlayerTextDrawBackgroundColor(p,TDError[p][5], 255);
	PlayerTextDrawFont(p,TDError[p][5], 1);
	PlayerTextDrawLetterSize(p,TDError[p][5], 0.240000, 1.100000);
	PlayerTextDrawColor(p,TDError[p][5], 255);
	PlayerTextDrawSetOutline(p,TDError[p][5], 0);
	PlayerTextDrawSetProportional(p,TDError[p][5], 1);
	PlayerTextDrawSetShadow(p,TDError[p][5], 0);
	PlayerTextDrawUseBox(p,TDError[p][5], 1);
	PlayerTextDrawBoxColor(p,TDError[p][5], -1);
	PlayerTextDrawTextSize(p,TDError[p][5], 456.000000, 41.000000);
	PlayerTextDrawSetSelectable(p,TDError[p][5],1);
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock Tamanho(playerid,Float:x,Float:y){
	PlayerTextDrawHide(playerid,TDMediaPlayer[playerid][7]);
	PlayerTextDrawTextSize(playerid,TDMediaPlayer[playerid][7], x, y);
	PlayerTextDrawShow(playerid,TDMediaPlayer[playerid][7]);
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock ExibirErro(playerid,titulo[],mensagem[]){
	PlayerTextDrawSetString(playerid,TDError[playerid][2],titulo);
	PlayerTextDrawSetString(playerid,TDError[playerid][3],mensagem);
	for(new t=0;t<6;t++) PlayerTextDrawShow(playerid,TDError[playerid][t]);
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock OcultarErro(playerid){
	for(new t=0;t<6;t++) PlayerTextDrawHide(playerid,TDError[playerid][t]);
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock NomeJogador(playerid)
{
	new nome[MAX_PLAYER_NAME]; GetPlayerName(playerid,nome,MAX_PLAYER_NAME);
	return nome;
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock ProfileDe(playerid)
{
	new profile[46];format(profile,sizeof(profile),"contas_rpg/%s.txt",NomeJogador(playerid));
	return profile;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock Celular(playerid){
	
	new celular[24]; format(celular,24,"celulares/%d.ini",dini_Int(ProfileDe(playerid),"NumeroCelular"));	
	return celular;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock CelularNumero(numero){
	
	new celular[24]; format(celular,24,"celulares/%d.ini",numero);	
	return celular;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock DestruirCelular(playerid)
{
	for(new t=0;t<61;t++) PlayerTextDrawDestroy(playerid,TDCelular[playerid][t]);
	for(new t=0;t<10;t++) PlayerTextDrawDestroy(playerid,TDCelularInterface[playerid][t]);
	for(new t=0;t<13;t++) PlayerTextDrawDestroy(playerid,TDMediaPlayer[playerid][t]);
	for(new t=0;t<6;t++) PlayerTextDrawDestroy(playerid,TDError[playerid][t]);
	for(new t=0;t<9;t++) PlayerTextDrawDestroy(playerid,GeniusTD[playerid][t]);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock CelularON(playerid) return CelularInfo[playerid][ligado];
//----------------------------------------------------------------------------------------------------------------------------------------
stock CelularLigado(playerid,bool:onoff)
{
	dini_IntSet(Celular(playerid),"ligado",(onoff)?(1):(0));
	CelularInfo[playerid][ligado]=onoff;
	if(onoff==false)
	{
		OcultarTDMenu(playerid);
		OcultarTDDiscador(playerid);
		OcultarTDOpcoes(playerid);
		OcultarTDInterface(playerid);
		OcultarTDDetalhes(playerid);
		PlayerTextDrawHide(playerid,TDCelular[playerid][59]);
		ExibirTDDisplayDesligado(playerid);
	}	
	else
	{
		OcultarTDDisplayDesligado(playerid);
		ExibirTDWallpaper(playerid);
		ExibirTDDetalhes(playerid);	
		PlayerTextDrawShow(playerid,TDCelular[playerid][59]);		
	}
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirTelaInicial(playerid)
{
	ExibirTDAparelho(playerid);
	OcultarTDMenu(playerid);
	OcultarTDDiscador(playerid);
	OcultarTDOpcoes(playerid);
	OcultarTDInterface(playerid);
	OcultarTDGenius(playerid);
	ExibirTDWallpaper(playerid);
	ExibirTDDetalhes(playerid);	
	SelectTextDraw(playerid, 0xFFFFFF3A);
	SetPVarInt(playerid,"Menu",NENHUM);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirDiscador(playerid)
{
	ExibirTDAparelho(playerid);
	OcultarTDMenu(playerid);	
	OcultarTDOpcoes(playerid);
	OcultarTDInterface(playerid);
	OcultarTDDetalhes(playerid);	
	ExibirTDWallpaper(playerid);
	ExibirTDDiscador(playerid);	
	ExibirTDDisplayDiscador(playerid);	
	SelectTextDraw(playerid, 0xFFFFFF3A);
	SetPVarInt(playerid,"Menu",DISCADOR);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirConfiguracoes(playerid)
{
	for(new t=3;t<8;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"toque");
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"papel de parede");
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"cor");
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][6],"privado");
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][7],"meu numero");
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][8],"_");
	PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][9],"_");
	OcultarTDMenu(playerid);
	OcultarTDDetalhes(playerid);
	for(new t=3;t<8;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);
	SetPVarInt(playerid,"Menu",CONFIGURACOES);
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirMenu(playerid)
{
	OcultarTDDiscador(playerid);
	OcultarTDOpcoes(playerid);
	OcultarTDInterface(playerid);
	OcultarTDDetalhes(playerid);
	OcultarTDGenius(playerid);
	OcultarMediaPlayer(playerid);
	ExibirTDWallpaper(playerid);
	ExibirTDMenu(playerid);
	PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Menu");
	SelectTextDraw(playerid, 0xFFFFFF3A);
	SetPVarInt(playerid,"Menu",PRINCIPAL);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirCelular(playerid,bool:forced)
{
	ExibirTDAparelho(playerid);
	if(!forced) SelectTextDraw(playerid, 0xFFFFFF3A);
	
	if(CelularInfo[playerid][ligado]==false){		
		ExibirTDDisplayDesligado(playerid);
		PlayerTextDrawHide(playerid,TDCelular[playerid][59]);
		return 0;
	}	
	OcultarTDDisplayDesligado(playerid);
		
	if(GetPVarInt(playerid,"ChamadaParaAtender")==1) ExibirTDDisplay(playerid);
	else ExibirTDWallpaper(playerid);
	
	ExibirTDDetalhes(playerid);		
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock OcultarCelular(playerid)
{
	for(new t=0;t<61;t++) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
	for(new t=0;t<10;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
	for(new t=0;t<13;t++) PlayerTextDrawHide(playerid,TDMediaPlayer[playerid][t]);
	for(new t=0;t<6;t++) PlayerTextDrawHide(playerid,TDError[playerid][t]);
	for(new t=0;t<9;t++) PlayerTextDrawHide(playerid,GeniusTD[playerid][t]);	
	CancelSelectTextDraw(playerid);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EditarDisplay(playerid,string[])
{
	if(strlen(string)){ 
		PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][1],string);
		OcultarTDOpcoes(playerid);
		OcultarTDInterface(playerid);
		OcultarTDDetalhes(playerid);	
		OcultarTDWallpaper(playerid);
		OcultarTDMenu(playerid);
		OcultarTDDiscador(playerid);
		OcultarTDDisplayDiscador(playerid);
		ExibirTDDisplay(playerid);				
	}	
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EditarDisplayDiscador(playerid,tipo,string[])
{
	new display[10];
	GetPVarString(playerid,"DisplayDiscador",display,10);
	switch(tipo){
		case 1: format(display,10,"%s%s",display,string); 
		case 2: format(display,10,"%s",string); 
		default: if(strlen(display)>1) strdel(display,strlen(display)-1,strlen(display)); else format(display,10,"_"); 
	}
	if(strlen(display)){ 
		SetPVarString(playerid,"DisplayDiscador",display);
		PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][0],display);		
		ExibirTDDisplayDiscador(playerid);
	}	
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock CriarNumero(playerid)
{
	new numero_aleatorio[10];format(numero_aleatorio,10,"9669%d%d%d%d",random(10),random(10),random(10),random(10));	
	new numero = strval(numero_aleatorio);
	
	while(fexist(CelularNumero(numero))){
		format(numero_aleatorio,10,"9669%d%d%d%d",random(10),random(10),random(10),random(10));	
		numero = strval(numero_aleatorio);
	}
		
	dini_Create(CelularNumero(numero));
	dini_IntSet(CelularNumero(numero),"criado",1);
	dini_Set(CelularNumero(numero),"dono",NomeJogador(playerid));
	dini_IntSet(CelularNumero(numero),"numero",numero);		
	dini_IntSet(ProfileDe(playerid),"NumeroCelular",numero);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExcluirNumero(playerid)
{	
	dini_IntSet(ProfileDe(playerid),"NumeroCelular",0);
	fremove(Celular(playerid));		
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock SalvarNumeroNaAgenda(playerid,numero,passo){
	switch(passo){
		case 1:{
			SetPVarInt(playerid,"NumeroContato",numero);
			ShowPlayerDialog(playerid,DIALOG_CONTATO,DIALOG_STYLE_INPUT,"Salvando contato...","Digite o nome do contato:","Salvar","Cancelar");
		}
		case 2:{			
			new contato[12];
			new contato_livre;
			for(new c = 1; c < 8; c++){
				format(contato,12,"contato%d",c);
				if(!dini_Isset(Celular(playerid),contato)){
					contato_livre = c;
					break;
				}
			}				
			if(contato_livre){
				new nome[24]; GetPVarString(playerid,"NomeContato",nome,24);
				if(!strlen(nome)) format(nome,24,"sem nome");
				
				format(contato,12,"contato%d",contato_livre);
				new descricao[35]; format(descricao,35,"%s/%d",nome,numero);
				dini_Set(Celular(playerid),contato,descricao);
				DeletePVar(playerid,"NomeContato");
				DeletePVar(playerid,"NumeroContato");
				EditarDisplayDiscador(playerid,2,"Salvo!");
			}
			return 1;
		}			
	}	
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExcluirNumeroNaAgenda(playerid,numero){
	new contato[12];
	new contato_info[33];
	new contato_numero[2][12];
	for(new c=1;c<8;c++){
		format(contato,12,"contato%d",c);
		if(dini_Isset(Celular(playerid),contato)){
			format(contato_info,33,"%s",dini_Get(Celular(playerid),contato));
			explode(contato_numero, contato_info, "/");
			if(numero == strval(contato_numero[1])){
				dini_Unset(Celular(playerid),contato);
				return EditarDisplayDiscador(playerid,2,"Excluido!");
			}
			else ExibirErro(playerid,"Erro","Numero nao existe na agenda!");
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock CarregarContato(playerid,contatoid){
	new contato[12];format(contato,12,"contato%d",contatoid);
	if(dini_Isset(Celular(playerid),contato)){
		new contato_info[33]; format(contato_info,33,"%s",dini_Get(Celular(playerid),contato));
		new contato_numero[2][12]; explode(contato_numero, contato_info, "/");		
		EditarDisplayDiscador(playerid,2,contato_numero[1]);
		OcultarTDOpcoes(playerid);
	}
	ExibirDiscador(playerid);
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirAgenda(playerid){
	OcultarTDMenu(playerid);	
	new contato[12];
	for(new c=1;c<8;c++){
		format(contato,12,"contato%d",c);
		if(dini_Isset(Celular(playerid),contato)){
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][c+2],dini_Get(Celular(playerid),contato));
		}
		else{
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][c+2],"LIVRE");
		}
		PlayerTextDrawShow(playerid,TDCelularInterface[playerid][c+2]);
		SetPVarInt(playerid,"Menu",AGENDA);
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock NumeroCelular(playerid)
{
	return dini_Int(ProfileDe(playerid),"NumeroCelular");
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PossuiCelular(playerid)
{
	return dini_Int(ProfileDe(playerid),"Celular");
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock AdquirirCelular(playerid)
{
	dini_IntSet(ProfileDe(playerid),"Celular",dini_Int(ProfileDe(playerid),"Celular")+1);	
	if(!NumeroCelular(playerid)) CriarNumero(playerid);
	VerificarDesejoDe(playerid,3);
	CriarAparelho(playerid);
	CarregarCelular(playerid);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PerderCelular(playerid)
{
	dini_IntSet(ProfileDe(playerid),"Celular",dini_Int(ProfileDe(playerid),"Celular")-1);
	if(!PossuiCelular(playerid)) ExcluirNumero(playerid);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PegarNumeroDiscador(playerid)
{
	new display[10]; GetPVarString(playerid,"DisplayDiscador",display,10);
	if(display[0]=='_') strdel(display,0,1);
	return strval(display);
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock Chamada(playerid)
{
	return CelularInfo[playerid][chamada];
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EmChamada(playerid)
{
	return CelularInfo[playerid][em_chamada];
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EncerrarChamada(playerid)
{
	if(CelularInfo[playerid][chamada]!=INVALID_PLAYER_ID)
	{	
		PlayerPlaySound(playerid,1063,0,0,0);
		
		new display[80];		
		if(GetPVarInt(playerid,"IniciouChamada")==1){
			format(display, sizeof(display), "Chamada finalizada...~n~Custo: R$%d",CelularInfo[playerid][custo_ligacao]);
			EditarDisplay(playerid,display);
			CallRemoteFunction("AcrescentarTaxa","ii",playerid,CelularInfo[playerid][custo_ligacao]);
		}
		else EditarDisplay(playerid,"Chamada finalizada...");
		
		new bCalling = CelularInfo[playerid][chamada];
		
		CelularInfo[playerid][custo_ligacao]=0;
		CelularInfo[playerid][chamada] = INVALID_PLAYER_ID;
	 	CelularInfo[playerid][em_chamada] = false;
		CelularInfo[playerid][ligando] = false;
		CallRemoteFunction("SetarCanal","ii",playerid,dini_Int(ProfileDe(playerid),"Chat"));

		if(IsPlayerConnected(bCalling))
		{
			EncerrarChamada(bCalling);
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZPhone_OnPlayerText(playerid, text[]);
public BRZPhone_OnPlayerText(playerid, text[])
{
	new msg[128]; format(msg, sizeof(msg), "[CELULAR] %s: %s",(CelularInfo[playerid][inibido])?("Desconhecido"):(NomeJogador(playerid)),text);
	SendClientMessage(CelularInfo[playerid][chamada], 0xADD8E6FF, msg);
	SendClientMessage(playerid, 0x87CEFAFF, msg);
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZPhone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
public BRZPhone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_CHAMADA_ESPECIAL:{
			if(response){
				if(strlen(inputtext)){
					CallRemoteFunction("EnviarChamadaEspecial","iis",playerid,GetPVarInt(playerid,"EscolhaMenu"),inputtext);
				}
			}
		}
		case DIALOG_CONTATO:{
			if(response){
				if(!strlen(inputtext)){
					ShowPlayerDialog(playerid,DIALOG_CONTATO,DIALOG_STYLE_INPUT,"Salvando contato...","Digite o nome do contato:","Salvar","Cancelar");
				}
				else{
					SetPVarString(playerid,"NomeContato",inputtext);
					SalvarNumeroNaAgenda(playerid,GetPVarInt(playerid,"NumeroContato"),2);
				}
			}
			else DeletePVar(playerid,"NomeContato"),DeletePVar(playerid,"NumeroContato");
		}
		case DIALOG_SMS:{
			if(response){
				if(!strlen(inputtext)){
					ShowPlayerDialog(playerid,DIALOG_SMS,DIALOG_STYLE_INPUT,"Enviando SMS...","Digite a mensagem:","Enviar","Cancelar");
				}
				else{
					EnviarSMS(playerid,1,inputtext);
				}
			}
			else DeletePVar(playerid,"NomeContato"),DeletePVar(playerid,"NumeroContato");
		}	
		case DIALOG_MEU_NUMERO:{
			if(response){
				if(!strlen(inputtext)){
					SolicitarNumero(playerid,1);
				}
				else{
					new novo_numero = strval(inputtext);
					if( novo_numero<10000000 || fexist(CelularNumero(novo_numero)) ) return SolicitarNumero(playerid,2);
					
					renomear(Celular(playerid),CelularNumero(novo_numero));
					dini_IntSet(ProfileDe(playerid),"NumeroCelular",novo_numero);
					dini_IntSet(Celular(playerid),"numero",novo_numero);
					
					ExibirConfiguracoes(playerid);
				}
			}
		}		
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock SMSNaoLida(playerid){
	new sms[6];
	new mensagem_completa[128];
	new naolidas = 0;
	for(new s=1;s<=7;s++){				
		format(sms,6,"sms%d",s);
		format(mensagem_completa,128,"%s",dini_Get(Celular(playerid),sms));		
		if(mensagem_completa[0]=='0') naolidas++;
	}
	return naolidas;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirSMS(playerid){
	OcultarTDMenu(playerid);
	OcultarTDOpcoes(playerid);
	OcultarTDDisplay(playerid);
	new sms[6];
	new mensagem[3][24];
	new exibir[30]; 
	new linha = 1;
	new mensagem_completa[128];
	for(new s=1;s<=7;s++){				
		format(sms,6,"sms%d",s);
		format(mensagem_completa,128,"%s",dini_Get(Celular(playerid),sms));
		
		if(strlen(mensagem_completa)){
			explode(mensagem,mensagem_completa,"§");
			format(exibir,30,"");	
			strcat(exibir,mensagem[1]);
			strcat(exibir,":");
			strcat(exibir,mensagem[2]);
			if(strval(mensagem[0])==0) strcat(exibir,"(new)");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][linha+2],exibir);
		}
		else PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][linha+2],"VAZIO");
		
		PlayerTextDrawShow(playerid,TDCelularInterface[playerid][linha+2]);		
		linha++;
	}
	DeletePVar(playerid,"LendoSMS");
	SetPVarInt(playerid,"Menu",SMS);
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock LerSMS(playerid,smsid){
	new sms[6];
	new mensagem_completa[128];
	format(sms,6,"sms%d",smsid);
	format(mensagem_completa,128,"%s",dini_Get(Celular(playerid),sms));
	if(strlen(mensagem_completa)){
		mensagem_completa[0]='1'; dini_Set(Celular(playerid),sms,mensagem_completa); 
		mensagem_completa[0]='_'; strins(mensagem_completa,"~n~_~n~_~n~",0);
		for(new c=0;c<strlen(mensagem_completa);c++){
			if(mensagem_completa[c]=='§'){ 
				mensagem_completa[c]='_';
				strins(mensagem_completa,"~n~",c);
			}	
		}
		if(strlen(mensagem_completa)){ 
			EditarDisplay(playerid,mensagem_completa);
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"voltar");
			PlayerTextDrawShow(playerid,TDCelularInterface[playerid][3]);
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"excluir");
			PlayerTextDrawShow(playerid,TDCelularInterface[playerid][4]);
			SetPVarInt(playerid,"LendoSMS",smsid);
		}
		SetPVarInt(playerid,"Menu",SMS);
		return 1;
	}	
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExcluirSMS(playerid,smsid){
	new sms[6];format(sms,6,"sms%d",smsid);
	dini_Unset(Celular(playerid),sms);
	DeletePVar(playerid,"LendoSMS");
	ExibirSMS(playerid);
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PegarCelular(playerid){
	if(!PossuiCelular(playerid)) return 0;
	
	if(!CelularInfo[playerid][em_maos]){
		DestruirCelular(playerid);
		CriarAparelho(playerid);
		CarregarCelular(playerid);
		ExibirCelular(playerid,false);
		CelularInfo[playerid][em_maos]=true;	
	}
	
	SelectTextDraw(playerid, 0xFFFFFF3A);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock GuardarCelular(playerid){
	OcultarCelular(playerid);
	DestruirCelular(playerid);	
	CelularInfo[playerid][em_maos]=false;
	CancelSelectTextDraw(playerid);
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock CelularEmMaos(playerid){
	return CelularInfo[playerid][em_maos];
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock AlertaDeMensagem(playerid){
	if(CelularInfo[playerid][ligado]){
		if(CelularInfo[playerid][em_maos]){
			ExibirAlerta(playerid,1);	
		}
		PlayerPlaySound(playerid,1057,0,0,0);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EnviarSMSEx(remetente[],destinatario,mensagem[]){
	if(IsPlayerConnected(destinatario)){						
		if(!fexist(Celular(destinatario))) return 0;
					
		new smsid,sms[6]; 
		for(new s=1;s<=12 && !smsid;s++){ 
			format(sms,6,"sms%d",s);
			if(!strlen(dini_Get(Celular(destinatario),sms))){
				smsid = s;
				break;
			}
		}
				
		if(smsid){
			new dia,mes,ano; getdate(ano,mes,dia);
			format(sms,6,"sms%d",smsid);				
			new texto_sms[128]; format(texto_sms,128,"0§%d/%d§%s§%s",dia,mes,remetente,mensagem);
			if(strlen(mensagem)) dini_Set(Celular(destinatario),sms,texto_sms);				
						
			AlertaDeMensagem(destinatario);
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EnviarSMS(playerid,passo,mensagem[]){
	switch(passo)
	{
		case 0:{
			SetPVarInt(playerid,"Menu",ENVIANDO_SMS);
			ShowPlayerDialog(playerid,DIALOG_SMS,DIALOG_STYLE_INPUT,"Enviando SMS...","Digite a mensagem:","Enviar","Cancelar");
		}
		case 1:{
			if(CallRemoteFunction("TaxasAPagar","i",playerid)>1000) return EditarDisplay(playerid,"Sua linha esta bloqueada por falta de pagamento...");

			new numero = PegarNumeroDiscador(playerid);		

			if(!fexist(CelularNumero(numero))) return ExibirErro(playerid,"Erro","Numero nao existe");

			new smsid,sms[6]; 
			for(new s=1;s<=12 && !smsid;s++){ 
				format(sms,6,"sms%d",s);
				if(!strlen(dini_Get(CelularNumero(numero),sms))){
					smsid = s;
					break;
				}
			}
				
			if(smsid){
				new dia,mes,ano; getdate(ano,mes,dia);
				format(sms,6,"sms%d",smsid);				
				new texto_sms[128]; format(texto_sms,128,"0§%d/%d§%s§%s",dia,mes,NomeJogador(playerid),mensagem);
				if(strlen(mensagem)) dini_Set(CelularNumero(numero),sms,texto_sms);
				
				new id_destinatario = IDDonoCelular(numero);		
				if(IsPlayerConnected(id_destinatario)){ 
					AlertaDeMensagem(playerid);
				}	
				EditarDisplayDiscador(playerid,2,"Enviada!");

				CallRemoteFunction("OnPlayerSendSMS","iss",playerid,DonoCelular(numero),mensagem);			
			}
			else{
				ExibirErro(playerid,"Erro","A caixa postal do destinatario cheia!");
			}
		}		
	}			
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock DonoCelular(numero){
	new destinatario[24]; format(destinatario,24,"%s",dini_Get(CelularNumero(numero),"dono"));
	return destinatario;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock IDDonoCelular(numero){
	new destinatario[24]; format(destinatario,24,"%s",dini_Get(CelularNumero(numero),"dono"));
	new id_destinatario = INVALID_PLAYER_ID;
	for(new i=0;i<BRAZUCAS_PLAYERS && id_destinatario==INVALID_PLAYER_ID;i++){
		if(!IsPlayerConnected(i)) continue;				
		if(!strcmp(destinatario,NomeJogador(i),false)){
			id_destinatario = i;
		}
	}
	return id_destinatario;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock SolicitarNumero(playerid,passo){
	new numero[128]; 
	switch(passo){
		case 0:format(numero,sizeof(numero),"Seu numero atual é %d\nPara alterar, digite um novo abaixo:",dini_Int(ProfileDe(playerid),"NumeroCelular"));
		case 1:format(numero,sizeof(numero),"Seu numero atual é %d\nPara alterar, digite um novo abaixo:\n\nVocê precisa inserir um número!",dini_Int(ProfileDe(playerid),"NumeroCelular"));
		case 2:format(numero,sizeof(numero),"Seu numero atual é %d\nPara alterar, digite um novo abaixo:\n\nNúmero inválido! Tente outro...",dini_Int(ProfileDe(playerid),"NumeroCelular"));
	}	
	return ShowPlayerDialog(playerid,DIALOG_MEU_NUMERO,DIALOG_STYLE_INPUT,"Meu numero...",numero,"Alterar","Voltar");
}
//-----------------------------------------------------------------------------------
stock OcultarTDInterface(playerid){
	for(new t=0;t<=9;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
}
stock ExibirTDInterface(playerid){
	for(new t=0;t<=9;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDMenu(playerid){
	for(new t=38;t<=46;t++) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
}
stock ExibirTDMenu(playerid){
	for(new t=38;t<=46;t++) PlayerTextDrawShow(playerid,TDCelular[playerid][t]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDDisplayDesligado(playerid){
	PlayerTextDrawHide(playerid,TDCelular[playerid][58]);
}
stock ExibirTDDisplayDesligado(playerid){
	PlayerTextDrawShow(playerid,TDCelular[playerid][58]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDOpcoes(playerid){
	for(new t=3;t<=9;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
}
stock ExibirTDOpcoes(playerid){
	for(new t=3;t<9;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDDisplayDiscador(playerid){
	PlayerTextDrawHide(playerid,TDCelularInterface[playerid][0]);
}
stock ExibirTDDisplayDiscador(playerid){
	PlayerTextDrawShow(playerid,TDCelularInterface[playerid][0]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDDisplay(playerid){
	PlayerTextDrawHide(playerid,TDCelularInterface[playerid][1]);
}
stock ExibirTDDisplay(playerid){
	PlayerTextDrawShow(playerid,TDCelularInterface[playerid][1]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDWallpaper(playerid){
	PlayerTextDrawHide(playerid,TDCelularInterface[playerid][2]);	
}
stock ExibirTDWallpaper(playerid){
	PlayerTextDrawShow(playerid,TDCelularInterface[playerid][2]);	
}
//-----------------------------------------------------------------------------------
stock OcultarTDDetalhes(playerid){
	for(new t=49;t<=56;t++) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
}
stock ExibirTDDetalhes(playerid){
	for(new t=49;t<=54;t++) PlayerTextDrawShow(playerid,TDCelular[playerid][t]);
	if(SMSNaoLida(playerid)>0) ExibirAlerta(playerid,1);
	if(GetPVarInt(playerid,"ChamadaNaoAtendida")>0) ExibirAlerta(playerid,2);
	PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"_");
}
//-----------------------------------------------------------------------------------
stock ExibirAlerta(playerid,alertaid){
	switch(alertaid){
		case 1:PlayerTextDrawShow(playerid,TDCelular[playerid][55]);
		case 2:PlayerTextDrawShow(playerid,TDCelular[playerid][56]);
	}
}
//-----------------------------------------------------------------------------------
stock OcultarTDDiscador(playerid){
	for(new t=26;t<=37;t++) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
	PlayerTextDrawHide(playerid,TDCelular[playerid][47]);
	PlayerTextDrawHide(playerid,TDCelular[playerid][48]);
}
stock ExibirTDDiscador(playerid){
	for(new t=26;t<=37;t++) PlayerTextDrawShow(playerid,TDCelular[playerid][t]);
	PlayerTextDrawShow(playerid,TDCelular[playerid][47]);
	PlayerTextDrawShow(playerid,TDCelular[playerid][48]);
}
//-----------------------------------------------------------------------------------
stock OcultarTDAparelho(playerid){
	for(new t=0;t<=25;t++) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
	PlayerTextDrawHide(playerid,TDCelular[playerid][57]);
	PlayerTextDrawHide(playerid,TDCelular[playerid][59]);
	PlayerTextDrawHide(playerid,TDCelular[playerid][60]);
}
stock ExibirTDAparelho(playerid){
	for(new t=0;t<=25;t++) PlayerTextDrawShow(playerid,TDCelular[playerid][t]);
	PlayerTextDrawShow(playerid,TDCelular[playerid][57]);
	PlayerTextDrawShow(playerid,TDCelular[playerid][59]);
	PlayerTextDrawShow(playerid,TDCelular[playerid][60]);	
}
//-----------------------------------------------------------------------------------
stock renomear(oldfile [], newfile []) // by [S]trong
{
    if (!fexist(oldfile))
    {
        return 0;
    }

    new String [256],
        File: oldarchive = fopen(oldfile, io_read),
        File: newarchive = fopen(newfile, io_write);

    while (fread(oldarchive, String))
    {
        fwrite(newarchive, String);
    }
    
    fclose(newarchive);
    fclose(oldarchive);

    return fremove(oldfile);
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock RegistrarChamada(remetente[],numero_remetente,destinatario[],numero_destinatario){
	new chamada_id[10];
	new chamada_registrada[34];
	for(new c=6;c>0;c--){
		format(chamada_id,10,"chamada%d",c);
		format(chamada_registrada,34,"%s",dini_Get(CelularNumero(numero_destinatario),chamada_id));
		format(chamada_id,10,"chamada%d",c+1);
		dini_Set(CelularNumero(numero_destinatario),chamada_id,chamada_registrada);
		
		format(chamada_id,10,"chamada%d",c);
		format(chamada_registrada,34,"%s",dini_Get(CelularNumero(numero_remetente),chamada_id));
		format(chamada_id,10,"chamada%d",c+1);
		dini_Set(CelularNumero(numero_remetente),chamada_id,chamada_registrada);			
	}
	format(chamada_registrada,34,"< %s %d",remetente,numero_remetente);
	dini_Set(CelularNumero(numero_destinatario),"chamada1",chamada_registrada);
	format(chamada_registrada,34,"> %s %d",destinatario,numero_destinatario);
	dini_Set(CelularNumero(numero_remetente),"chamada1",chamada_registrada);	
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirChamadas(playerid){
	OcultarTDMenu(playerid);
	new chamada_id[10];
	new chamada_registrada[34];
	
	for(new c=1;c<=7;c++){
		format(chamada_id,10,"chamada%d",c);
		format(chamada_registrada,34,"%s",dini_Get(Celular(playerid),chamada_id));
		
		if(strlen(chamada_registrada)){
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][c+2],chamada_registrada);
		}
		else{
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][c+2],"VAZIO");
		}
		PlayerTextDrawShow(playerid,TDCelularInterface[playerid][c+2]);
		SetPVarInt(playerid,"Menu",CHAMADAS);
	}
	PlayerTextDrawHide(playerid,TDCelular[playerid][56]);
	DeletePVar(playerid,"ChamadaNaoAtendida");
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock CarregarChamada(playerid,chamadaid){
	new chamada_id[10];format(chamada_id,10,"chamada%d",chamadaid);
	new chamada_registrada[34];format(chamada_registrada,34,"%s",dini_Get(Celular(playerid),chamada_id));
	
	if(strlen(chamada_registrada)){
		new chamada_completa[3][34]; explode(chamada_completa, chamada_registrada," ");		
		EditarDisplayDiscador(playerid,2,chamada_completa[2]);
		OcultarTDOpcoes(playerid);
	}
	ExibirDiscador(playerid);
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock AtualizarCor(playerid,corid,bool:show){
	for(new t=0;t<6;t++){ 
		if(show) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
		PlayerTextDrawBoxColor(playerid,TDCelular[playerid][t],CelularCores[corid]);
		PlayerTextDrawColor(playerid,TDCelular[playerid][t],CelularCores[corid]);
		PlayerTextDrawBackgroundColor(playerid,TDCelular[playerid][t],CelularCores[corid]);
		if(show) PlayerTextDrawShow(playerid,TDCelular[playerid][t]);
	}	
	for(new t=12;t<18;t++){ 
		if(show) PlayerTextDrawHide(playerid,TDCelular[playerid][t]);
		PlayerTextDrawBoxColor(playerid,TDCelular[playerid][t],CelularCores[corid]);
		PlayerTextDrawColor(playerid,TDCelular[playerid][t],CelularCores[corid]);
		PlayerTextDrawBackgroundColor(playerid,TDCelular[playerid][t],CelularCores[corid]);
		if(show) PlayerTextDrawShow(playerid,TDCelular[playerid][t]);			
	}

	CelularInfo[playerid][cor_celular]=corid;
	dini_IntSet(Celular(playerid),"cor",corid);
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock ChamadaEspecial(playerid,chamadaid){
	new titulo[45];
	new mensagem[125];
	switch(chamadaid){
		case 1:format(titulo,sizeof(titulo),"Departamento de Polícia'BRZ"),format(mensagem,sizeof(mensagem),"Digite sua mensagem e os policiais de plantão irão atendê-la:");
		case 2:format(titulo,sizeof(titulo),"Corpo de Bombeiros'BRZ"),format(mensagem,sizeof(mensagem),"Digite sua mensagem e os bombeiros de plantão irão atendê-la:");
		case 3:format(titulo,sizeof(titulo),"Serviço de Atendimento Móvel e Urgência'BRZ"),format(mensagem,sizeof(mensagem),"Digite sua mensagem e os enfermeiros de plantão irão atendê-la:");
		case 4:format(titulo,sizeof(titulo),"Companhia de Taxi'BRZ"),format(mensagem,sizeof(mensagem),"Digite o local aonde se encontra e enviaremos um taxi:");
		case 5:format(titulo,sizeof(titulo),"Disk Denúncias'BRZ"),format(mensagem,sizeof(mensagem),"Digite sua mensagem em um dos formatos:\nFurto:Placa do Veiculo Furtado\nAssalto:Nome do Assaltante\nFalsidade: Nome do Denunciado");
		case 6:format(titulo,sizeof(titulo),"Pizzarias'BRZ"),format(mensagem,sizeof(mensagem),"Digite o local aonde se encontra e enviaremos um pizzaboy:");
	}
	SetPVarInt(playerid,"EscolhaMenu",chamadaid);	
	ShowPlayerDialog(playerid,DIALOG_CHAMADA_ESPECIAL,DIALOG_STYLE_INPUT,titulo,mensagem,"Enviar","Cancelar");
}
//stocks
//----------------------------------------------------------------------------------------------------------------------------------------
forward ContaTempoChamada(playerid);
public ContaTempoChamada(playerid){
	if(IsPlayerConnected(playerid)){
		if(CelularInfo[playerid][em_chamada]==true){
			CelularInfo[playerid][custo_ligacao]++;
			new display[80];
			new minutos = floatround(CelularInfo[playerid][custo_ligacao] / 60);
			format(display,80,"Chamada ativa...~n~_~n~_~n~%s~n~Duracao: %02d:%02d",(CelularInfo[CelularInfo[playerid][chamada]][inibido])?("Desconhecido"):(NomeJogador(CelularInfo[playerid][chamada])),minutos,CelularInfo[playerid][custo_ligacao]-(minutos*60));
			EditarDisplay(playerid,display);
			if(CelularInfo[playerid][custo_ligacao]>20){
				CallRemoteFunction("VerificarDesejoDe","ii",playerid,37);
			}
			SetTimerEx("ContaTempoChamada",1000,false,"i",playerid);
		}
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------
forward TempoParaAtender(playerid);
public TempoParaAtender(playerid){
	if(IsPlayerConnected(playerid)){
	    if(CelularInfo[playerid][chamada] != INVALID_PLAYER_ID){
		    if(CelularInfo[playerid][em_chamada] == false){
		    	EditarDisplay(playerid,"Caixa Postal...");
				new nome[24]; GetPlayerName(CelularInfo[playerid][chamada],nome,24);
				if(CelularInfo[playerid][inibido]) format(nome,24,"Desconhecido"); else GetPlayerName(playerid,nome,24);
				
				new bCalling = CelularInfo[playerid][chamada];
				CelularInfo[playerid][chamada] = INVALID_PLAYER_ID;
				CelularInfo[playerid][em_chamada] = false;
				CelularInfo[playerid][ligando] = false;				
				
		    	ExibirAlerta(bCalling,2);
				DeletePVar(bCalling,"ChamadaParaAtender");	
				SetPVarInt(bCalling,"ChamadaNaoAtendida",1);				
				PlayerPlaySound(bCalling,1063,0,0,0);				
		   		CelularInfo[bCalling][chamada] = INVALID_PLAYER_ID;
		   		CelularInfo[bCalling][em_chamada] = false;
				CelularInfo[bCalling][ligando] = false;		
		    }
		}
	}
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZPhone_OnPlayerConnect(playerid);
public BRZPhone_OnPlayerConnect(playerid){
	CelularInfo[playerid][chamada]=INVALID_PLAYER_ID;
	CelularInfo[playerid][ligando]=false;
	CelularInfo[playerid][em_chamada]=false;
	CelularInfo[playerid][custo_ligacao]=0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZPhone_OnPlayerDisconnect(playerid);
public BRZPhone_OnPlayerDisconnect(playerid){
	CelularInfo[playerid][chamada]=INVALID_PLAYER_ID;
	CelularInfo[playerid][em_chamada]=false;
	CelularInfo[playerid][ligando]=false;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZPhone_OnPlayerClick(playerid,PlayerText:playertextid);
public BRZPhone_OnPlayerClick(playerid,PlayerText:playertextid){	
	
	if(CelularInfo[playerid][ligado]==false && playertextid != TDCelular[playerid][25]) return 0;
	
	Genius_OnPlayerClick(playerid,playertextid);
	
	if(playertextid == TDCelular[playerid][19]){ 
		ExibirMenu(playerid);
	}	
    else if(playertextid == TDCelular[playerid][23])
	{
		if(GetPVarInt(playerid,"Menu") == DISCADOR && CelularInfo[playerid][chamada] == INVALID_PLAYER_ID && CelularInfo[playerid][ligando] == false)
		{
			if(CallRemoteFunction("TaxasAPagar","i",playerid)>1000) return EditarDisplay(playerid,"Sua linha esta bloqueada por falta de pagamento...");

			new numero = PegarNumeroDiscador(playerid);		

			if(!fexist(CelularNumero(numero))) return ExibirErro(playerid,"Erro","Numero nao existe");

			new id_destinatario = IDDonoCelular(numero);	

			if(!IsPlayerConnected(id_destinatario)||CelularInfo[id_destinatario][ligado]==false) return EditarDisplay(playerid,"Fora de area...");			
			if(CallRemoteFunction("TaxasAPagar","i",id_destinatario)>1000) return EditarDisplay(playerid,"A linha do destinatario esta bloqueada...");
			if(CelularInfo[id_destinatario][chamada]!=INVALID_PLAYER_ID) return EditarDisplay(playerid,"Numero ocupado...");
 
			PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Chamada");	
			new display[35];format(display,35,"Chamando %s...",NomeJogador(id_destinatario)); EditarDisplay(playerid,display);								
			CelularInfo[playerid][chamada] = id_destinatario;			
			CelularInfo[playerid][ligando] = true;
			SetPVarInt(playerid,"IniciouChamada",1);									
			SetTimerEx("TempoParaAtender",10000,0,"i",playerid);
			
			CelularInfo[id_destinatario][chamada] = playerid;
			SetPVarInt(id_destinatario,"ChamadaParaAtender",1);
			
			if(!CelularInfo[id_destinatario][em_maos]){
				DestruirCelular(id_destinatario);
				CriarAparelho(id_destinatario);
				CarregarCelular(id_destinatario);
				ExibirCelular(id_destinatario,true);
				CelularInfo[id_destinatario][em_maos]=true;
			}
			
			PlayerTextDrawSetString(id_destinatario,TDCelular[id_destinatario][59],"Chamada");	
			format(display,35,"%s chamando...",(CelularInfo[playerid][inibido])?("Desconhecido"):(NomeJogador(playerid))); EditarDisplay(id_destinatario,display);
			PlayerPlaySound(id_destinatario,Toques[CelularInfo[playerid][toque]],0,0,0);
			
			RegistrarChamada(NomeJogador(playerid),NumeroCelular(playerid),NomeJogador(id_destinatario),NumeroCelular(id_destinatario));
		}
		else if(IsPlayerConnected(CelularInfo[playerid][chamada]) && GetPVarInt(playerid,"ChamadaParaAtender")==1)
		{				
			if(CelularInfo[playerid][em_chamada] == true) return EditarDisplay(playerid,"Ligacao em andamento...");

			DeletePVar(playerid,"ChamadaParaAtender");						
			PlayerPlaySound(playerid,1063,0,0,0);
					
			SetTimerEx("ContaTempoChamada",1000,false,"i",playerid);
			SetTimerEx("ContaTempoChamada",1000,false,"i",CelularInfo[playerid][chamada]);

			CelularInfo[playerid][em_chamada] = true;
			CelularInfo[CelularInfo[playerid][chamada]][em_chamada] = true;
			CelularInfo[CelularInfo[playerid][chamada]][ligando] = true;
					
			CallRemoteFunction("SetarCanal","ii",playerid,6);
			CallRemoteFunction("SetarCanal","ii",CelularInfo[playerid][chamada],6);									
		}
		else
		{
			for(new t=3;t<10;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"190");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"193");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"199");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][6],"TAXI");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][7],"DISK DENUNCIA");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][8],"PIZZA");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][9],"voltar");
			OcultarTDMenu(playerid);
			OcultarTDDetalhes(playerid);
			for(new t=3;t<10;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);
			SetPVarInt(playerid,"Menu",CHAMADAS_ESPECIAIS);
		}
    }
    else if(playertextid == TDCelular[playerid][25]){
        if (IsPlayerConnected(CelularInfo[playerid][chamada])){			
	        EncerrarChamada(playerid);
		}
		else{
			switch(GetPVarInt(playerid,"Menu")){
				case NENHUM:{
					//print("ligar/desligar");
					CelularLigado(playerid,!CelularInfo[playerid][ligado]);
				}
				case PRINCIPAL:{
					//print("ir para tela inicial");
					ExibirTelaInicial(playerid);
				}
				default:{
					//print("ir para menu principal");
					if(Genius[playerid][jogando]) DeixarJogo(playerid);
					ExibirMenu(playerid);	
				}
			}	
		}
    }
    else if(playertextid == TDCelular[playerid][26]) EditarDisplayDiscador(playerid,1,"1");
    else if(playertextid == TDCelular[playerid][27]) EditarDisplayDiscador(playerid,1,"2");
    else if(playertextid == TDCelular[playerid][28]) EditarDisplayDiscador(playerid,1,"3");
    else if(playertextid == TDCelular[playerid][29]) EditarDisplayDiscador(playerid,1,"4");
    else if(playertextid == TDCelular[playerid][30]) EditarDisplayDiscador(playerid,1,"5");
    else if(playertextid == TDCelular[playerid][31]) EditarDisplayDiscador(playerid,1,"6");
    else if(playertextid == TDCelular[playerid][32]) EditarDisplayDiscador(playerid,1,"7");
    else if(playertextid == TDCelular[playerid][33]) EditarDisplayDiscador(playerid,1,"8");
    else if(playertextid == TDCelular[playerid][34]) EditarDisplayDiscador(playerid,1,"9");
    else if(playertextid == TDCelular[playerid][36]) EditarDisplayDiscador(playerid,1,"0");
    else if(playertextid == TDCelular[playerid][37]) EditarDisplayDiscador(playerid,0," ");
    
	//menu principal
	else if(playertextid == TDCelular[playerid][38]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Discador");
        ExibirDiscador(playerid);
    }	
	else if(playertextid == TDCelular[playerid][39]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Configuracoes");
		ExibirConfiguracoes(playerid);
	}
	else if(playertextid == TDCelular[playerid][40]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"GPS");
		if(CallRemoteFunction("IniciarGPS","i",playerid)){
			SetPVarInt(playerid,"Menu",GPS);
		}
	}
	else if(playertextid == TDCelular[playerid][41]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Banco");
		if(CallRemoteFunction("CriarStringMiniBalanco","i",playerid)){
			new balanco[256]; GetPVarString(playerid,"MiniBalanco",balanco,256);
			EditarDisplay(playerid,balanco);
			SetPVarInt(playerid,"Menu",BANCO);
		}
	}	
	else if(playertextid == TDCelular[playerid][42] || playertextid == TDCelular[playerid][55]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Mensagens");
		ExibirSMS(playerid);
	}	
	else if(playertextid == TDCelular[playerid][43]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Media Player");
		ExibirMediaPlayer(playerid);
	}
	else if(playertextid == TDCelular[playerid][44]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Agenda");
		ExibirAgenda(playerid);
	}
	else if(playertextid == TDCelular[playerid][45] || playertextid == TDCelular[playerid][56]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Chamadas");
		ExibirChamadas(playerid);
	}
	else if(playertextid == TDCelular[playerid][46]){
		PlayerTextDrawSetString(playerid,TDCelular[playerid][59],"Jogos");
		ExibirMenuGenius(playerid,0);
	}	
	
	else if(playertextid >= TDCelularInterface[playerid][3] && playertextid <= TDCelularInterface[playerid][9]){
		switch(GetPVarInt(playerid,"Menu")){
			case GENIUS:{
				if(playertextid == TDCelularInterface[playerid][3]) OcultarTDOpcoes(playerid),ExibirTDGenius(playerid);
				else if(playertextid == TDCelularInterface[playerid][4]) ExibirMenuGenius(playerid,1);
				else if(playertextid == TDCelularInterface[playerid][5]) ExibirMenu(playerid);
			}
			case GENIUS_DIFICULDADE:{
				if(playertextid == TDCelularInterface[playerid][3]) Genius[playerid][dificuldade]=1000,ExibirMenuGenius(playerid,0);
				else if(playertextid == TDCelularInterface[playerid][4]) Genius[playerid][dificuldade]=500,ExibirMenuGenius(playerid,0);
				else if(playertextid == TDCelularInterface[playerid][5]) Genius[playerid][dificuldade]=250,ExibirMenuGenius(playerid,0);		
			}
			case CHAMADAS_ESPECIAIS:
			{
				if(playertextid == TDCelularInterface[playerid][3]) ChamadaEspecial(playerid,1);
				else if(playertextid == TDCelularInterface[playerid][4]) ChamadaEspecial(playerid,2);
				else if(playertextid == TDCelularInterface[playerid][5]) ChamadaEspecial(playerid,3);
				else if(playertextid == TDCelularInterface[playerid][6]) ChamadaEspecial(playerid,4);
				else if(playertextid == TDCelularInterface[playerid][7]) ChamadaEspecial(playerid,5);
				else if(playertextid == TDCelularInterface[playerid][8]) ChamadaEspecial(playerid,6);
				else if(playertextid == TDCelularInterface[playerid][9]) ExibirTelaInicial(playerid);
			}
			case SMS:{
				if(GetPVarInt(playerid,"LendoSMS")!=0){
					if(playertextid == TDCelularInterface[playerid][3]) ExibirSMS(playerid);
					else if(playertextid == TDCelularInterface[playerid][4]) ExcluirSMS(playerid,GetPVarInt(playerid,"LendoSMS"));
				}
				else{
					if(playertextid == TDCelularInterface[playerid][3]) LerSMS(playerid,1);
					else if(playertextid == TDCelularInterface[playerid][4]) LerSMS(playerid,2);
					else if(playertextid == TDCelularInterface[playerid][5]) LerSMS(playerid,3);
					else if(playertextid == TDCelularInterface[playerid][6]) LerSMS(playerid,4);
					else if(playertextid == TDCelularInterface[playerid][7]) LerSMS(playerid,5);
					else if(playertextid == TDCelularInterface[playerid][8]) LerSMS(playerid,6);
					else if(playertextid == TDCelularInterface[playerid][9]) LerSMS(playerid,7);
				}	
			}
			case AGENDA:{
				if(playertextid == TDCelularInterface[playerid][3]) CarregarContato(playerid,1);
				else if(playertextid == TDCelularInterface[playerid][4]) CarregarContato(playerid,2);
				else if(playertextid == TDCelularInterface[playerid][5]) CarregarContato(playerid,3); 
				else if(playertextid == TDCelularInterface[playerid][6]) CarregarContato(playerid,4); 
				else if(playertextid == TDCelularInterface[playerid][7]) CarregarContato(playerid,5);
				else if(playertextid == TDCelularInterface[playerid][8]) CarregarContato(playerid,6);
				else if(playertextid == TDCelularInterface[playerid][9]) CarregarContato(playerid,7); 
			}
			case CONFIGURACOES:{
				if(playertextid == TDCelularInterface[playerid][3]){
					for(new t=3;t<8;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"Proximo >>");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Anterior <<");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"Selecionar");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][6],"Parar");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][7],"Voltar");
					for(new t=3;t<8;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);				
					SetPVarInt(playerid,"Menu",TOQUE);
					SetPVarInt(playerid,"EscolhaMenu",0);
					PlayerPlaySound(playerid,Toques[GetPVarInt(playerid,"EscolhaMenu")],0,0,0);
				}
				if(playertextid == TDCelularInterface[playerid][4]){
					for(new t=3;t<8;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"Proximo >>");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Anterior <<");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"Selecionar");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][6],"Voltar");
					for(new t=3;t<7;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);				
					SetPVarInt(playerid,"Menu",PAPEL_DE_PAREDE);
					SetPVarInt(playerid,"EscolhaMenu",0);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][2],Wallpapers[GetPVarInt(playerid,"EscolhaMenu")]);
					PlayerTextDrawShow(playerid,TDCelularInterface[playerid][2]);
				}
				if(playertextid == TDCelularInterface[playerid][5]){
					for(new t=3;t<8;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"Proximo >>");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Anterior <<");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"Voltar");
					for(new t=3;t<6;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);				
					SetPVarInt(playerid,"Menu",CORES);
					SetPVarInt(playerid,"EscolhaMenu",0);
					AtualizarCor(playerid,GetPVarInt(playerid,"EscolhaMenu"),true);
				}
				if(playertextid == TDCelularInterface[playerid][6]){
					for(new t=3;t<8;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"Sim");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Nao");
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"Voltar");
					for(new t=3;t<6;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);				
					SetPVarInt(playerid,"Menu",INIBIDO);
				}
				if(playertextid == TDCelularInterface[playerid][7]){
					for(new t=3;t<8;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
					new numero[10]; format(numero,10,"%d",dini_Int(ProfileDe(playerid),"NumeroCelular"));
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],numero);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Voltar");
					for(new t=3;t<5;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);
					SetPVarInt(playerid,"Menu",MEU_NUMERO);
				}
			}
			case TOQUE:{
				if(playertextid == TDCelularInterface[playerid][3]){
					SetPVarInt(playerid,"EscolhaMenu",GetPVarInt(playerid,"EscolhaMenu")+1);
					if(GetPVarInt(playerid,"EscolhaMenu")>9) SetPVarInt(playerid,"EscolhaMenu",0);
					PlayerPlaySound(playerid,Toques[GetPVarInt(playerid,"EscolhaMenu")],0,0,0);
				}
				else if(playertextid == TDCelularInterface[playerid][4]){
					SetPVarInt(playerid,"EscolhaMenu",GetPVarInt(playerid,"EscolhaMenu")-1);
					if(GetPVarInt(playerid,"EscolhaMenu")<0) SetPVarInt(playerid,"EscolhaMenu",9);
					PlayerPlaySound(playerid,Toques[GetPVarInt(playerid,"EscolhaMenu")],0,0,0);
				}
				else if(playertextid == TDCelularInterface[playerid][5]){					
					dini_IntSet(Celular(playerid),"toque",GetPVarInt(playerid,"EscolhaMenu"));
					CelularInfo[playerid][toque]=GetPVarInt(playerid,"EscolhaMenu");										
					DeletePVar(playerid,"EscolhaMenu");					
				}
				else if(playertextid == TDCelularInterface[playerid][6]){
					PlayerPlaySound(playerid,1063,0.0,0.0,0.0);
				}
				else if(playertextid == TDCelularInterface[playerid][7]){
					ExibirConfiguracoes(playerid);
				}				
			}
			case PAPEL_DE_PAREDE:{
				if(playertextid == TDCelularInterface[playerid][3]){
					SetPVarInt(playerid,"EscolhaMenu",GetPVarInt(playerid,"EscolhaMenu")+1);
					if(GetPVarInt(playerid,"EscolhaMenu")>17) SetPVarInt(playerid,"EscolhaMenu",0);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][2],Wallpapers[GetPVarInt(playerid,"EscolhaMenu")]);
					PlayerTextDrawShow(playerid,TDCelularInterface[playerid][2]);
				}
				else if(playertextid == TDCelularInterface[playerid][4]){
					SetPVarInt(playerid,"EscolhaMenu",GetPVarInt(playerid,"EscolhaMenu")-1);
					if(GetPVarInt(playerid,"EscolhaMenu")<0) SetPVarInt(playerid,"EscolhaMenu",17);
					PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][2],Wallpapers[GetPVarInt(playerid,"EscolhaMenu")]);
					PlayerTextDrawShow(playerid,TDCelularInterface[playerid][2]);
				}
				else if(playertextid == TDCelularInterface[playerid][5]){
					dini_IntSet(Celular(playerid),"wallpaper",GetPVarInt(playerid,"EscolhaMenu"));
					CelularInfo[playerid][papel_de_parede]=GetPVarInt(playerid,"EscolhaMenu");
					DeletePVar(playerid,"EscolhaMenu");
					ExibirMenu(playerid);
				}
				else if(playertextid == TDCelularInterface[playerid][6]){					
					ExibirConfiguracoes(playerid);		
				}				
			}
			case INIBIDO:{
				if(playertextid == TDCelularInterface[playerid][3]) CelularInfo[playerid][inibido]=true;
				else if(playertextid == TDCelularInterface[playerid][4]) CelularInfo[playerid][inibido]=false;
				
				dini_IntSet(Celular(playerid),"inibido",(CelularInfo[playerid][inibido]==true)?(1):(0));	
				
				if(playertextid == TDCelularInterface[playerid][5]) ExibirConfiguracoes(playerid);						
			}
			case MEU_NUMERO:{
				if(playertextid == TDCelularInterface[playerid][3]) SolicitarNumero(playerid,0);
				else if(playertextid == TDCelularInterface[playerid][4]) ExibirConfiguracoes(playerid);	
			}
			case CHAMADAS:{
				if(playertextid == TDCelularInterface[playerid][3]) CarregarChamada(playerid,1);
				else if(playertextid == TDCelularInterface[playerid][4]) CarregarChamada(playerid,2);
				else if(playertextid == TDCelularInterface[playerid][5]) CarregarChamada(playerid,3); 
				else if(playertextid == TDCelularInterface[playerid][6]) CarregarChamada(playerid,4); 
				else if(playertextid == TDCelularInterface[playerid][7]) CarregarChamada(playerid,5);
				else if(playertextid == TDCelularInterface[playerid][8]) CarregarChamada(playerid,6);
				else if(playertextid == TDCelularInterface[playerid][9]) CarregarChamada(playerid,7); 
			}
			case CORES:{
				if(playertextid == TDCelularInterface[playerid][3]){
					SetPVarInt(playerid,"EscolhaMenu",GetPVarInt(playerid,"EscolhaMenu")+1);
					if(GetPVarInt(playerid,"EscolhaMenu")>9) SetPVarInt(playerid,"EscolhaMenu",0);
					AtualizarCor(playerid,GetPVarInt(playerid,"EscolhaMenu"),true);
				}
				else if(playertextid == TDCelularInterface[playerid][4]){
					SetPVarInt(playerid,"EscolhaMenu",GetPVarInt(playerid,"EscolhaMenu")-1);
					if(GetPVarInt(playerid,"EscolhaMenu")<0) SetPVarInt(playerid,"EscolhaMenu",9);
					AtualizarCor(playerid,GetPVarInt(playerid,"EscolhaMenu"),true);
				}
				else if(playertextid == TDCelularInterface[playerid][5]){					
					ExibirConfiguracoes(playerid);										
					DeletePVar(playerid,"EscolhaMenu");					
				}		
			}			
		}
	}
	else if(playertextid == TDCelular[playerid][47]){		
		new numero = PegarNumeroDiscador(playerid);
		if(numero<10000000) return ExibirErro(playerid,"Erro","Numero invalido...");
		SalvarNumeroNaAgenda(playerid,numero,1);				
	}
	else if(playertextid == TDCelular[playerid][48]){
		new numero = PegarNumeroDiscador(playerid);
		if(numero<10000000) return ExibirErro(playerid,"Erro","Numero invalido...");
		ExcluirNumeroNaAgenda(playerid,numero);	
	}
	else if(playertextid == TDCelular[playerid][35]){
		new numero = PegarNumeroDiscador(playerid);
		if(numero<10000000) return ExibirErro(playerid,"Erro","Numero invalido...");
		EnviarSMS(playerid,0,"_");
	}	
	else if(playertextid == TDMediaPlayer[playerid][4]){
		PlayAudioStreamForPlayer(playerid,"http://bit.ly/rR8Rw4");
		PlayerTextDrawHide(playerid,TDMediaPlayer[playerid][4]);
		PlayerTextDrawShow(playerid,TDMediaPlayer[playerid][5]);
		CelularInfo[playerid][player_tocando]=true;
	}
	else if(playertextid == TDMediaPlayer[playerid][5]){
		PlayerTextDrawHide(playerid,TDMediaPlayer[playerid][5]);
		PlayerTextDrawShow(playerid,TDMediaPlayer[playerid][4]);	
		StopAudioStreamForPlayer(playerid);
		CelularInfo[playerid][player_tocando]=false;
	}
	else if(playertextid == TDError[playerid][5]){
		OcultarErro(playerid);
	}	
	return 0;
}
//------------------------------------------------------------------------------------------------------------
stock CriarGeniusTD(p){
	GeniusTD[p][0] = CreatePlayerTextDraw(p,437.000000, 298.000000, "_");
	PlayerTextDrawAlignment(p,GeniusTD[p][0], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][0], 255);
	PlayerTextDrawFont(p,GeniusTD[p][0], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][0], 0.280000, 11.600002);
	PlayerTextDrawColor(p,GeniusTD[p][0], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][0], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][0], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][0], 1);
	PlayerTextDrawUseBox(p,GeniusTD[p][0], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][0], 200);
	PlayerTextDrawTextSize(p,GeniusTD[p][0], 1.000000, 59.000000);

	GeniusTD[p][1] = CreatePlayerTextDraw(p,437.000000, 302.000000, "Genius");
	PlayerTextDrawAlignment(p,GeniusTD[p][1], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][1], 255);
	PlayerTextDrawFont(p,GeniusTD[p][1], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][1], 0.250000, 1.699999);
	PlayerTextDrawColor(p,GeniusTD[p][1], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][1], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][1], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][1], 1);

	GeniusTD[p][2] = CreatePlayerTextDraw(p,436.000000, 384.500000, "_");
	PlayerTextDrawAlignment(p,GeniusTD[p][2], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][2], 255);
	PlayerTextDrawFont(p,GeniusTD[p][2], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][2], 0.230000, 1.200000);
	PlayerTextDrawColor(p,GeniusTD[p][2], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][2], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][2], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][2], 1);

	GeniusTD[p][3] = CreatePlayerTextDraw(p,417.000000, 324.000000, "_");
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][3], 255);
	PlayerTextDrawFont(p,GeniusTD[p][3], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][3], 0.500000, 5.900000);
	PlayerTextDrawColor(p,GeniusTD[p][3], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][3], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][3], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][3], 2);
	PlayerTextDrawUseBox(p,GeniusTD[p][3], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][3], 1684301055);
	PlayerTextDrawTextSize(p,GeniusTD[p][3], 457.000000, 1.000000);

	GeniusTD[p][4] = CreatePlayerTextDraw(p,426.000000, 325.000000, "_");
	PlayerTextDrawAlignment(p,GeniusTD[p][4], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][4], 255);
	PlayerTextDrawFont(p,GeniusTD[p][4], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][4], 0.500000, 2.399999);
	PlayerTextDrawColor(p,GeniusTD[p][4], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][4], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][4], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][4], 1);
	PlayerTextDrawUseBox(p,GeniusTD[p][4], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][4], -16776961);
	PlayerTextDrawTextSize(p,GeniusTD[p][4], 23.000000, 17.000000);
	PlayerTextDrawSetSelectable(p,GeniusTD[p][4],1);	

	GeniusTD[p][5] = CreatePlayerTextDraw(p,448.000000, 325.000000, "_");
	PlayerTextDrawAlignment(p,GeniusTD[p][5], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][5], 255);
	PlayerTextDrawFont(p,GeniusTD[p][5], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][5], 0.500000, 2.399999);
	PlayerTextDrawColor(p,GeniusTD[p][5], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][5], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][5], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][5], 1);
	PlayerTextDrawUseBox(p,GeniusTD[p][5], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][5], 16711935);
	PlayerTextDrawTextSize(p,GeniusTD[p][5], 23.000000, 17.000000);
	PlayerTextDrawSetSelectable(p,GeniusTD[p][5],1);	

	GeniusTD[p][6] = CreatePlayerTextDraw(p,426.000000, 354.000000, "_");
	PlayerTextDrawAlignment(p,GeniusTD[p][6], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][6], 255);
	PlayerTextDrawFont(p,GeniusTD[p][6], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][6], 0.500000, 2.399999);
	PlayerTextDrawColor(p,GeniusTD[p][6], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][6], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][6], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][6], 1);
	PlayerTextDrawUseBox(p,GeniusTD[p][6], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][6], 65535);
	PlayerTextDrawTextSize(p,GeniusTD[p][6], 23.000000, 17.000000);
	PlayerTextDrawSetSelectable(p,GeniusTD[p][6],1);	

	GeniusTD[p][7] = CreatePlayerTextDraw(p,448.000000, 354.000000, "_");
	PlayerTextDrawAlignment(p,GeniusTD[p][7], 2);
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][7], 255);
	PlayerTextDrawFont(p,GeniusTD[p][7], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][7], 0.500000, 2.399999);
	PlayerTextDrawColor(p,GeniusTD[p][7], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][7], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][7], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][7], 1);
	PlayerTextDrawUseBox(p,GeniusTD[p][7], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][7], -65281);
	PlayerTextDrawTextSize(p,GeniusTD[p][7], 23.000000, 17.000000);
	PlayerTextDrawSetSelectable(p,GeniusTD[p][7],1);	

	GeniusTD[p][8] = CreatePlayerTextDraw(p,467.000000, 295.000000, "Pontos: 0");
	PlayerTextDrawBackgroundColor(p,GeniusTD[p][8], 255);
	PlayerTextDrawAlignment(p,GeniusTD[p][8], 3);
	PlayerTextDrawFont(p,GeniusTD[p][8], 1);
	PlayerTextDrawLetterSize(p,GeniusTD[p][8], 0.150000, 0.800000);
	PlayerTextDrawColor(p,GeniusTD[p][8], -1);
	PlayerTextDrawSetOutline(p,GeniusTD[p][8], 0);
	PlayerTextDrawSetProportional(p,GeniusTD[p][8], 1);
	PlayerTextDrawSetShadow(p,GeniusTD[p][8], 0);
	PlayerTextDrawUseBox(p,GeniusTD[p][8], 1);
	PlayerTextDrawBoxColor(p,GeniusTD[p][8], -256);
	PlayerTextDrawTextSize(p,GeniusTD[p][8], 10.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,GeniusTD[p][8],1);
	return 1;
}
stock ExibirTDGenius(playerid){
	SetTimerEx("IniciarJogo",2000,false,"i",playerid);
	PlayerTextDrawSetString(playerid,GeniusTD[playerid][2],"Prepare-se...");
	for(new t=0;t<9;t++) PlayerTextDrawShow(playerid,GeniusTD[playerid][t]);
	SetPVarInt(playerid,"Menu",GENIUS);
	return 1;
}
stock OcultarTDGenius(playerid){
	for(new t=0;t<9;t++) PlayerTextDrawHide(playerid,GeniusTD[playerid][t]);	
	return 1;
}
stock DeixarJogo(playerid){
	Genius[playerid][jogando]=false;
	OcultarTDGenius(playerid);
	return ExibirMenu(playerid);
}
forward ApagarQuadro(playerid,quadroid);
public ApagarQuadro(playerid,quadroid){
	if(!Genius[playerid][jogando]) return 0;
	//printf("apaga quadro %d...",quadroid);
	PlayerTextDrawHide(playerid,GeniusTD[playerid][quadroid+3]);	
	SetTimerEx("AcenderQuadro",Genius[playerid][dificuldade] / 2,false,"ii",playerid,quadroid);
	return 1;
}
forward AcenderQuadro(playerid,quadroid);
public AcenderQuadro(playerid,quadroid){
	if(!Genius[playerid][jogando]) return 0;
	//printf("acende quadro %d...",quadroid);
	PlayerPlaySound(playerid,GeniusSons[quadroid-1],0,0,0);
	PlayerTextDrawShow(playerid,GeniusTD[playerid][quadroid+3]);
	return 1;
}
forward PiscarSequencia(playerid,jogadaid);
public PiscarSequencia(playerid,jogadaid){
	if(!Genius[playerid][jogando]) return 0;
	//printf("pisca sequencia ate jogada %d...",jogadaid);
	ApagarQuadro(playerid,Genius[playerid][jogada_esperada][Genius[playerid][piscadas]]);
	if(Genius[playerid][piscadas]<jogadaid){
		Genius[playerid][piscadas]++;
		SetTimerEx("PiscarSequencia",Genius[playerid][dificuldade],false,"ii",playerid,jogadaid);
	}
	return 1;
}
forward ProximaRodada(playerid);
public ProximaRodada(playerid){
	if(!Genius[playerid][jogando]) return 0;
	//print("proxima rodada...");
	new jogadas = Genius[playerid][jogada];	
	Genius[playerid][jogada_esperada][jogadas]=random(4)+1;
	//printf("rodada %d, jogada esperada %d...",jogadas,Genius[playerid][jogada_esperada][jogadas]);
	Genius[playerid][piscadas]=0;
	Genius[playerid][sequencia]=0;
	PiscarSequencia(playerid,jogadas);
	new score_info[24]; format(score_info,24,"Pontos: %d",Genius[playerid][pontos_conseguidos]);
	PlayerTextDrawSetString(playerid,GeniusTD[playerid][8],score_info);
	PlayerTextDrawSetString(playerid,GeniusTD[playerid][2],"...");
	return 1;
}
stock ExibirMenuGenius(playerid,menuid){
	OcultarTDMenu(playerid);
	switch(menuid){
		case 0:{
			for(new t=3;t<6;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"Iniciar");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Dificuldade");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"Sair");
			for(new t=3;t<6;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);				
			SetPVarInt(playerid,"Menu",GENIUS);
		}
		case 1:{
			for(new t=3;t<6;t++) PlayerTextDrawHide(playerid,TDCelularInterface[playerid][t]);
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][3],"Facil");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][4],"Medio");
			PlayerTextDrawSetString(playerid,TDCelularInterface[playerid][5],"Dificil");
			for(new t=3;t<6;t++) PlayerTextDrawShow(playerid,TDCelularInterface[playerid][t]);				
			SetPVarInt(playerid,"Menu",GENIUS_DIFICULDADE);		
		}
	}	
}
forward IniciarJogo(playerid);
public IniciarJogo(playerid){
	OcultarTDOpcoes(playerid);
	//print("iniciando jogo");
	Genius[playerid][jogando]=true;
	Genius[playerid][jogada]=0;	
	Genius[playerid][pontos_conseguidos]=0;
	if(!Genius[playerid][dificuldade]) Genius[playerid][dificuldade]=1000;
	return ProximaRodada(playerid);
}
stock ChecarJogada(playerid,quadroid){
	//printf("rodada %d, jogada realizada %d...",Genius[playerid][jogada],quadroid);
	new sequencia_checada = Genius[playerid][sequencia];
	new score_info[24];
	Genius[playerid][jogada_realizada][sequencia_checada]=quadroid;
	ApagarQuadro(playerid,quadroid);
	//print("checando sequencia...");	
	
	//printf("jogada esperada %d, jogada realizada %d...",Genius[playerid][jogada_esperada][sequencia_checada],Genius[playerid][jogada_realizada][sequencia]);
	if(Genius[playerid][jogada_esperada][sequencia_checada]!=Genius[playerid][jogada_realizada][sequencia_checada]){
		Genius[playerid][jogando]=false;
		format(score_info,24,"Pontos: %d",Genius[playerid][pontos_conseguidos]);
		PlayerTextDrawSetString(playerid,GeniusTD[playerid][8],score_info);
		return PlayerTextDrawSetString(playerid,GeniusTD[playerid][2],"Perdeu!");
	}
	else{
		if(sequencia_checada==Genius[playerid][jogada]){
			if(Genius[playerid][jogada]==20){
				Genius[playerid][jogando]=false;
				format(score_info,24,"Pontos: %d",Genius[playerid][pontos_conseguidos]);
				PlayerTextDrawSetString(playerid,GeniusTD[playerid][8],score_info);
				return PlayerTextDrawSetString(playerid,GeniusTD[playerid][2],"Venceu!");
			}
			else{
				Genius[playerid][jogada]++;
				SetTimerEx("ProximaRodada",1000,false,"i",playerid);
				format(score_info,24,"Pontos: %d",Genius[playerid][pontos_conseguidos]);
				PlayerTextDrawSetString(playerid,GeniusTD[playerid][8],score_info);
				PlayerTextDrawSetString(playerid,GeniusTD[playerid][2],"Acertou!");			
			}
		}
		else Genius[playerid][pontos_conseguidos]++,Genius[playerid][sequencia]++;
	}
	return 0;	
}
stock Genius_OnPlayerClick(playerid,PlayerText:playertextid){
	if(Genius[playerid][jogando]){
		if(playertextid == GeniusTD[playerid][8]) DeixarJogo(playerid);
		else if(playertextid == GeniusTD[playerid][4]) ChecarJogada(playerid,1);
		else if(playertextid == GeniusTD[playerid][5]) ChecarJogada(playerid,2);
		else if(playertextid == GeniusTD[playerid][6]) ChecarJogada(playerid,3);
		else if(playertextid == GeniusTD[playerid][7]) ChecarJogada(playerid,4);
	}
	return 1;
}
//--------------------------------------------------------------------------------------------------------------------------------
stock ExibirMediaPlayer(playerid){
	OcultarTDMenu(playerid);
	for(new t=0;t<13;t++){
		switch(t){
			case 4: if(!CelularInfo[playerid][player_tocando]) PlayerTextDrawShow(playerid,TDMediaPlayer[playerid][t]);
			case 5: if(CelularInfo[playerid][player_tocando]) PlayerTextDrawShow(playerid,TDMediaPlayer[playerid][t]);
			default:PlayerTextDrawShow(playerid,TDMediaPlayer[playerid][t]);
		}	
	}
	SetPVarInt(playerid,"Menu",MEDIA_PLAYER);
	return 1;
}
//--------------------------------------------------------------------------------------------------------------------------------
forward EditarDisplayMediaPlayer(playerid,string[]);
public EditarDisplayMediaPlayer(playerid,string[]){
	if(!IsPlayerConnected(playerid)) return 0;
	if(!strlen(string)) return 0;
	PlayerTextDrawSetString(playerid,TDMediaPlayer[playerid][12],string);
	return 1;
}
//--------------------------------------------------------------------------------------------------------------------------------
stock OcultarMediaPlayer(playerid){
	for(new t=0;t<13;t++) PlayerTextDrawHide(playerid,TDMediaPlayer[playerid][t]);
	return 1;
}
//--------------------------------------------------------------------------------------------------------------------------------
stock AtualizarRelogio(hora,minuto){
	new str_relogio[5];format(str_relogio,5,"%d:%d",hora,minuto);
	return PlayerTextDrawSetString(playerid,TDCelular[playerid][55],strrelogio);
}