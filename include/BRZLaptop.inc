/*
	Brazucas'Laptop
	ok	- msn	(linkar ao sistema do rpg)
	ok	- configuracoes	(criar)
	ok		- papel de parede (criar)
	ok		- cor (criar)
	ok	- browser (linkar ao sistema do rpg)
	ok		- prefeitura (enviar curriculo)
			- policia
				- localizar jogador / veiculo
				- chamar reforço
				- mais procurados
				- procurados
				- presos
				- consultar multas de veículo
				- pesquisar por modelos de veículos
				- lista de suspeitos
				- ultimos crimes
				- denuncias
	ok		- detran
	ok		- shopping
	ok			- casas a venda
	ok			- veiculos a venda
	ok			- propriedades a venda
	ok			- itens diversos				
	ok	- banco 
	ok	- balanco
	ok	- extrato
	ok	- transferencias
	ok	- pagar dividas
	ok	- investimento
	ok	- cambio
		- email
			- caixa de entrada
			- excluir email
			- ler email
			- enviar email
	ok 	- gps
		- player
		- webcam / um jogo 

			
*/
#include <a_samp>

#define DESKTOP				0
#define PLANO_DE_FUNDO		1
#define CONFIGURACOES		2
#define CORES_LAPTOP		3
#define BROWSER				4
#define MSN					5
#define CHAT				6
#define GPS_LAPTOP			7
#define BANKLINE			8
#define JOGOS				9
#define SALA				10
#define PAGINA_SHOPPING		11
#define EMAIL				12
#define CAIXA_DE_ENTRADA	13
#define LENDO_EMAIL			14
#define ESCREVENDO_EMAIL	15
#define PAGINA_POLICIA		16
#define PAGINA_DETRAN		17
#define PAGINA_PREFEITURA	18
#define PAGINA_FTP_INICIO 19


new LaptopWallpapers[][0]={"LOADSUK:loadsc8","LOADSUK:loadsc9","LOADSUK:loadscuk","LOADSUK:loadsc7","LOADSUK:loadsc6","LOADSUK:loadsc5","LOADSUK:loadsc4","LOADSUK:loadsc3","LOADSUK:loadsc2","LOADSUK:loadsc14","LOADSUK:loadsc13","LOADSUK:loadsc12","LOADSUK:loadsc11","LOADSUK:loadsc10","LOADSUK:loadsc1","LOADSCS:nvidia","LOADSCS:title_pc_US","load0uk:load0uk"};
new LaptopCores[]={0x000000FF,0xE6E6E6FF,0x000000FF,0xFFFFFFFF,0xFF8200FF,0xA000FFFF,0xAFFF00FF,0xE837A1FF,0x54AB04FF,0xE0B600FF,0x535355FF,0xF4941CFF,0xFF1C1FFF,0x53379EFF,0x007EB8FF};
new LinhasChat[5][10][128];

new PlayerText:TDLaptop[BRAZUCAS_PLAYERS][23];
new PlayerText:TDLaptopMenu[BRAZUCAS_PLAYERS][12];
new PlayerText:TDLaptopWallpaper[BRAZUCAS_PLAYERS];
new PlayerText:TDLaptopJanela[BRAZUCAS_PLAYERS][20];

enum laptop_info{
	bool:ligado,	
	papel_de_parede,
	cor_laptop,
	bool:em_maos
}
new LaptopInfo[BRAZUCAS_PLAYERS][laptop_info];
//----------------------------------------------------------------------------------------------------------------------------------
stock CarregarLaptop(playerid)
{
	if(fexist(Laptop(playerid)))
	{
		LaptopInfo[playerid][papel_de_parede]=dini_Int(Laptop(playerid),"wallpaper");
		LaptopInfo[playerid][cor_laptop]=dini_Int(Laptop(playerid),"cor");
	}
	if(LaptopInfo[playerid][ligado]){
		PlayerTextDrawColor(playerid,TDLaptop[playerid][21], -16776961);
		PlayerTextDrawColor(playerid,TDLaptop[playerid][22], -16776961);		
		ExibirAreaDeTrabalho(playerid);
	}	
	AtualizarCorLaptop(playerid,LaptopInfo[playerid][cor_laptop],false);
	AtualizarPapelDeParede(playerid,LaptopInfo[playerid][papel_de_parede],false);
	PlayerTextDrawSetString(playerid,TDLaptopWallpaper[playerid],LaptopWallpapers[LaptopInfo[playerid][papel_de_parede]]);
}
//----------------------------------------------------------------------------------------------------------------------------------
stock CriarLaptop(p)
{
	TDLaptop[p][0] = CreatePlayerTextDraw(p,319.500000, 129.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][0], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][0], 255);
	PlayerTextDrawFont(p,TDLaptop[p][0], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][0], 0.500000, 21.000000);
	PlayerTextDrawColor(p,TDLaptop[p][0], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][0], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][0], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][0], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][0], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][0], 151587327);
	PlayerTextDrawTextSize(p,TDLaptop[p][0], 70.000000, 308.000000);

	TDLaptop[p][1] = CreatePlayerTextDraw(p,320.000000, 120.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][1], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][1], 255);
	PlayerTextDrawFont(p,TDLaptop[p][1], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][1], 0.500000, 21.600002);
	PlayerTextDrawColor(p,TDLaptop[p][1], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][1], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][1], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][1], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][1], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][1], 151587327);
	PlayerTextDrawTextSize(p,TDLaptop[p][1], 70.000000, 297.000000);

	TDLaptop[p][2] = CreatePlayerTextDraw(p,177.500000, 138.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][2], 151587327);
	PlayerTextDrawFont(p,TDLaptop[p][2], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][2], -0.599999, -2.399998);
	PlayerTextDrawColor(p,TDLaptop[p][2], 151587327);
	PlayerTextDrawSetOutline(p,TDLaptop[p][2], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][2], 1);

	TDLaptop[p][3] = CreatePlayerTextDraw(p,474.500000, 138.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][3], 151587327);
	PlayerTextDrawFont(p,TDLaptop[p][3], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][3], -0.599999, -2.399998);
	PlayerTextDrawColor(p,TDLaptop[p][3], 151587327);
	PlayerTextDrawSetOutline(p,TDLaptop[p][3], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][3], 1);

	TDLaptop[p][4] = CreatePlayerTextDraw(p,320.000000, 322.500000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][4], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][4], 255);
	PlayerTextDrawFont(p,TDLaptop[p][4], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][4], 0.500000, 2.400000);
	PlayerTextDrawColor(p,TDLaptop[p][4], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][4], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][4], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][4], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][4], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][4], 151587327);
	PlayerTextDrawTextSize(p,TDLaptop[p][4], 70.000000, 370.000000);

	TDLaptop[p][5] = CreatePlayerTextDraw(p,320.000000, 325.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][5], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][5], 255);
	PlayerTextDrawFont(p,TDLaptop[p][5], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][5], 0.500000, 3.099998);
	PlayerTextDrawColor(p,TDLaptop[p][5], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][5], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][5], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][5], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][5], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][5], 151587327);
	PlayerTextDrawTextSize(p,TDLaptop[p][5], 70.000000, 337.000000);

	TDLaptop[p][6] = CreatePlayerTextDraw(p,128.500000, 310.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][6], 151587327);
	PlayerTextDrawFont(p,TDLaptop[p][6], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][6], 1.890001, 5.499999);
	PlayerTextDrawColor(p,TDLaptop[p][6], 151587327);
	PlayerTextDrawSetOutline(p,TDLaptop[p][6], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][6], 0);

	TDLaptop[p][7] = CreatePlayerTextDraw(p,472.500000, 310.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][7], 151587327);
	PlayerTextDrawFont(p,TDLaptop[p][7], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][7], 1.890001, 5.499999);
	PlayerTextDrawColor(p,TDLaptop[p][7], 151587327);
	PlayerTextDrawSetOutline(p,TDLaptop[p][7], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][7], 0);

	TDLaptop[p][8] = CreatePlayerTextDraw(p,319.500000, 132.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][8], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][8], 255);
	PlayerTextDrawFont(p,TDLaptop[p][8], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][8], 0.500000, 21.000000);
	PlayerTextDrawColor(p,TDLaptop[p][8], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][8], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][8], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][8], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][8], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][8], 255);
	PlayerTextDrawTextSize(p,TDLaptop[p][8], 70.000000, 305.000000);

	TDLaptop[p][9] = CreatePlayerTextDraw(p,320.000000, 122.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][9], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][9], 255);
	PlayerTextDrawFont(p,TDLaptop[p][9], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][9], 0.500000, 21.600002);
	PlayerTextDrawColor(p,TDLaptop[p][9], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][9], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][9], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][9], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][9], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][9], 255);
	PlayerTextDrawTextSize(p,TDLaptop[p][9], 70.000000, 297.000000);

	TDLaptop[p][10] = CreatePlayerTextDraw(p,178.500000, 140.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][10], 255);
	PlayerTextDrawFont(p,TDLaptop[p][10], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][10], -0.599999, -2.399997);
	PlayerTextDrawColor(p,TDLaptop[p][10], 255);
	PlayerTextDrawSetOutline(p,TDLaptop[p][10], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][10], 1);

	TDLaptop[p][11] = CreatePlayerTextDraw(p,473.500000, 140.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][11], 255);
	PlayerTextDrawFont(p,TDLaptop[p][11], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][11], -0.599999, -2.399997);
	PlayerTextDrawColor(p,TDLaptop[p][11], 255);
	PlayerTextDrawSetOutline(p,TDLaptop[p][11], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][11], 1);

	TDLaptop[p][12] = CreatePlayerTextDraw(p,316.000000, 322.500000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][12], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][12], 255);
	PlayerTextDrawFont(p,TDLaptop[p][12], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][12], 0.500000, 2.400000);
	PlayerTextDrawColor(p,TDLaptop[p][12], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][12], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][12], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][12], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][12], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][12], 255);
	PlayerTextDrawTextSize(p,TDLaptop[p][12], 69.000000, 364.000000);

	TDLaptop[p][13] = CreatePlayerTextDraw(p,320.000000, 325.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][13], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][13], 255);
	PlayerTextDrawFont(p,TDLaptop[p][13], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][13], 0.500000, 2.899997);
	PlayerTextDrawColor(p,TDLaptop[p][13], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][13], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][13], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][13], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][13], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][13], 255);
	PlayerTextDrawTextSize(p,TDLaptop[p][13], 70.000000, 337.000000);

	TDLaptop[p][14] = CreatePlayerTextDraw(p,129.500000, 313.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][14], 255);
	PlayerTextDrawFont(p,TDLaptop[p][14], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][14], 1.900001, 4.999999);
	PlayerTextDrawColor(p,TDLaptop[p][14], 255);
	PlayerTextDrawSetOutline(p,TDLaptop[p][14], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][14], 0);

	TDLaptop[p][15] = CreatePlayerTextDraw(p,471.500000, 313.000000, "U");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][15], 255);
	PlayerTextDrawFont(p,TDLaptop[p][15], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][15], 1.900001, 4.999999);
	PlayerTextDrawColor(p,TDLaptop[p][15], 255);
	PlayerTextDrawSetOutline(p,TDLaptop[p][15], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][15], 0);

	TDLaptop[p][16] = CreatePlayerTextDraw(p,320.000000, 322.500000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][16], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][16], 255);
	PlayerTextDrawFont(p,TDLaptop[p][16], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][16], 0.500000, -0.300000);
	PlayerTextDrawColor(p,TDLaptop[p][16], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][16], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][16], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][16], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][16], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][16], 151587327);
	PlayerTextDrawTextSize(p,TDLaptop[p][16], 70.000000, 372.000000);

	TDLaptop[p][17] = CreatePlayerTextDraw(p,320.000000, 139.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][17], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][17], 255);
	PlayerTextDrawFont(p,TDLaptop[p][17], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][17], 0.500000, 18.599998);
	PlayerTextDrawColor(p,TDLaptop[p][17], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][17], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][17], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][17], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][17], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][17], 255);
	PlayerTextDrawTextSize(p,TDLaptop[p][17], 0.000000, 290.000000);

	TDLaptop[p][18] = CreatePlayerTextDraw(p,321.000000, 329.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][18], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][18], 255);
	PlayerTextDrawFont(p,TDLaptop[p][18], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][18], 1.570000, 0.999998);
	PlayerTextDrawColor(p,TDLaptop[p][18], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][18], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][18], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][18], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][18], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][18], 505290495);
	PlayerTextDrawTextSize(p,TDLaptop[p][18], 0.000000, 36.000000);

	TDLaptop[p][19] = CreatePlayerTextDraw(p,321.000000, 330.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptop[p][19], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][19], 255);
	PlayerTextDrawFont(p,TDLaptop[p][19], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][19], 1.570000, 0.699998);
	PlayerTextDrawColor(p,TDLaptop[p][19], -1);
	PlayerTextDrawSetOutline(p,TDLaptop[p][19], 0);
	PlayerTextDrawSetProportional(p,TDLaptop[p][19], 1);
	PlayerTextDrawSetShadow(p,TDLaptop[p][19], 1);
	PlayerTextDrawUseBox(p,TDLaptop[p][19], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][19], 255);
	PlayerTextDrawTextSize(p,TDLaptop[p][19], -2.000000, 33.000000);

	TDLaptop[p][20] = CreatePlayerTextDraw(p,315.000000, 121.000000, "O");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][20], 505290495);
	PlayerTextDrawFont(p,TDLaptop[p][20], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][20], 0.330000, 1.500000);
	PlayerTextDrawColor(p,TDLaptop[p][20], 255);
	PlayerTextDrawSetOutline(p,TDLaptop[p][20], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][20], 1);

	TDLaptop[p][21] = CreatePlayerTextDraw(p,457.000000, 311.000000, "O");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][21], 255);
	PlayerTextDrawFont(p,TDLaptop[p][21], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][21], 0.230000, 0.899999);
	PlayerTextDrawColor(p,TDLaptop[p][21], -16776961);
	PlayerTextDrawSetOutline(p,TDLaptop[p][21], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][21], 1);

	TDLaptop[p][22] = CreatePlayerTextDraw(p,459.000000, 311.000000, "l");
	PlayerTextDrawBackgroundColor(p,TDLaptop[p][22], 255);
	PlayerTextDrawFont(p,TDLaptop[p][22], 1);
	PlayerTextDrawLetterSize(p,TDLaptop[p][22], 0.230000, 0.499998);
	PlayerTextDrawColor(p,TDLaptop[p][22], -16776961);
	PlayerTextDrawSetOutline(p,TDLaptop[p][22], 1);
	PlayerTextDrawSetProportional(p,TDLaptop[p][22], 1);	
	PlayerTextDrawUseBox(p,TDLaptop[p][22], 1);
	PlayerTextDrawBoxColor(p,TDLaptop[p][22], -256);
	PlayerTextDrawTextSize(p,TDLaptop[p][22], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptop[p][22],1);
		
	TDLaptopWallpaper[p] = CreatePlayerTextDraw(p,173.000000, 137.000000, "LOADSUK:loadsc8");
	PlayerTextDrawBackgroundColor(p,TDLaptopWallpaper[p],255);
	PlayerTextDrawFont(p,TDLaptopWallpaper[p], 4);
	PlayerTextDrawLetterSize(p,TDLaptopWallpaper[p], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopWallpaper[p], -1);
	PlayerTextDrawSetOutline(p,TDLaptopWallpaper[p], 0);
	PlayerTextDrawSetProportional(p,TDLaptopWallpaper[p], 1);
	PlayerTextDrawSetShadow(p,TDLaptopWallpaper[p], 1);
	PlayerTextDrawUseBox(p,TDLaptopWallpaper[p], 1);
	PlayerTextDrawBoxColor(p,TDLaptopWallpaper[p], 255);
	PlayerTextDrawTextSize(p,TDLaptopWallpaper[p], 294.000000, 172.000000);
	
	TDLaptopMenu[p][0] = CreatePlayerTextDraw(p,320.000000, 292.000000, "_");
	PlayerTextDrawAlignment(p,TDLaptopMenu[p][0], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][0], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][0], 1);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][0], 0.500000, 1.600000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][0], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][0], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][0], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][0], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][0], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][0], -217);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][0], 465.000000, 150.000000);

	TDLaptopMenu[p][1] = CreatePlayerTextDraw(p,320.000000, 292.500000, "_");
	PlayerTextDrawAlignment(p,TDLaptopMenu[p][1], 2);
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][1], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][1], 1);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][1], 0.500000, 1.600000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][1], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][1], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][1], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][1], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][1], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][1], 137);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][1], 465.000000, 149.000000);

	TDLaptopMenu[p][2] = CreatePlayerTextDraw(p,245.000000, 292.000000, "LD_CHAT:goodcha");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][2], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][2], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][2], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][2], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][2], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][2], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][2], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][2], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][2], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][2], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][2], 1);

	TDLaptopMenu[p][3] = CreatePlayerTextDraw(p,260.000000, 292.000000, "LD_NONE:warp");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][3], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][3], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][3], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][3], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][3], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][3], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][3], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][3], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][3], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][3], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][3], 1);

	TDLaptopMenu[p][4] = CreatePlayerTextDraw(p,275.000000, 292.000000, "hud:radar_cash");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][4], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][4], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][4], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][4], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][4], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][4], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][4], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][4], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][4], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][4], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][4], 1);

	TDLaptopMenu[p][5] = CreatePlayerTextDraw(p,290.000000, 292.000000, "LD_CHAT:badchat");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][5], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][5], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][5], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][5], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][5], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][5], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][5], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][5], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][5], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][5], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][5], 1);

	TDLaptopMenu[p][6] = CreatePlayerTextDraw(p,305.000000, 292.000000, "hud:radar_Flag");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][6], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][6], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][6], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][6], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][6], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][6], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][6], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][6], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][6], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][6], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][6], 1);

	TDLaptopMenu[p][7] = CreatePlayerTextDraw(p,320.000000, 292.000000, "hud:radar_impound");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][7], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][7], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][7], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][7], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][7], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][7], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][7], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][7], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][7], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][7], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][7], 1);

	TDLaptopMenu[p][8] = CreatePlayerTextDraw(p,335.000000, 292.000000, "hud:radar_tshirt");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][8], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][8], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][8], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][8], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][8], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][8], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][8], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][8], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][8], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][8], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][8], 1);

	TDLaptopMenu[p][9] = CreatePlayerTextDraw(p,350.000000, 292.000000, "hud:radar_mafiaCasino");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][9], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][9], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][9], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][9], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][9], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][9], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][9], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][9], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][9], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][9], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][9], 1);

	TDLaptopMenu[p][10] = CreatePlayerTextDraw(p,365.000000, 292.000000, "hud:radar_dateDisco");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][10], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][10], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][10], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][10], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][10], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][10], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][10], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][10], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][10], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][10], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][10], 1);

	TDLaptopMenu[p][11] = CreatePlayerTextDraw(p,380.000000, 292.000000, "hud:radar_modGarage");
	PlayerTextDrawBackgroundColor(p,TDLaptopMenu[p][11], 255);
	PlayerTextDrawFont(p,TDLaptopMenu[p][11], 4);
	PlayerTextDrawLetterSize(p,TDLaptopMenu[p][11], 0.500000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopMenu[p][11], -1);
	PlayerTextDrawSetOutline(p,TDLaptopMenu[p][11], 0);
	PlayerTextDrawSetProportional(p,TDLaptopMenu[p][11], 1);
	PlayerTextDrawSetShadow(p,TDLaptopMenu[p][11], 1);
	PlayerTextDrawUseBox(p,TDLaptopMenu[p][11], 1);
	PlayerTextDrawBoxColor(p,TDLaptopMenu[p][11], 255);
	PlayerTextDrawTextSize(p,TDLaptopMenu[p][11], 14.000000, 16.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopMenu[p][11], 1);
	
	TDLaptopJanela[p][0] = CreatePlayerTextDraw(p,175.000000, 139.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][0], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][0], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][0], 0.239999, 18.500001);
	PlayerTextDrawColor(p,TDLaptopJanela[p][0], -1);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][0], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][0], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][0], 1);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][0], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][0], -190);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][0], 465.000000, 0.000000);

	TDLaptopJanela[p][1] = CreatePlayerTextDraw(p,178.000000, 153.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][1], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][1], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][1], 0.239999, 16.699995);
	PlayerTextDrawColor(p,TDLaptopJanela[p][1], -1);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][1], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][1], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][1], 1);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][1], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][1], -1);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][1], 462.000000, 0.000000);

	TDLaptopJanela[p][2] = CreatePlayerTextDraw(p,175.000000, 139.000000, "Meu Computador");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][2], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][2], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][2], 0.230000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopJanela[p][2], -1);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][2], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][2], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][2], 1);

	TDLaptopJanela[p][3] = CreatePlayerTextDraw(p,438.000000, 138.000000, "-");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][3], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][3], 2);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][3], 0.489998, 1.600000);
	PlayerTextDrawColor(p,TDLaptopJanela[p][3], -1);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][3], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][3], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][3], 1);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][3], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][3], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][3], 444.000000, 10.000000);

	TDLaptopJanela[p][4] = CreatePlayerTextDraw(p,446.000000, 139.000000, "o");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][4], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][4], 2);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][4], 0.230000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopJanela[p][4], -1);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][4], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][4], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][4], 1);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][4], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][4], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][4], 453.000000, 0.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][4],1);

	TDLaptopJanela[p][5] = CreatePlayerTextDraw(p,455.000000, 139.000000, "x");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][5], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][5], 2);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][5], 0.230000, 1.000000);
	PlayerTextDrawColor(p,TDLaptopJanela[p][5], -1);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][5], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][5], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][5], 1);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][5], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][5], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][5], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][5],1);

	TDLaptopJanela[p][6] = CreatePlayerTextDraw(p,179.000000, 155.000000, "_");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][6], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][6], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][6], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][6], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][6], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][6], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][6], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][6], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][6], 255);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][6], 461.000000, 10.000000);

	TDLaptopJanela[p][7] = CreatePlayerTextDraw(p,179.000000, 168.000000, "Link2");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][7], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][7], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][7], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][7], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][7], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][7], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][7], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][7], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][7], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][7], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][7],1);

	TDLaptopJanela[p][8] = CreatePlayerTextDraw(p,179.000000, 180.000000, "Link3");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][8], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][8], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][8], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][8], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][8], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][8], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][8], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][8], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][8], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][8], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][8],1);

	TDLaptopJanela[p][9] = CreatePlayerTextDraw(p,179.000000, 193.000000, "Link4");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][9], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][9], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][9], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][9], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][9], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][9], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][9], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][9], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][9], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][9], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][9],1);

	TDLaptopJanela[p][10] = CreatePlayerTextDraw(p,179.000000, 205.000000, "Link5");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][10], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][10], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][10], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][10], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][10], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][10], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][10], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][10], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][10], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][10], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][10],1);

	TDLaptopJanela[p][11] = CreatePlayerTextDraw(p,179.000000, 218.000000, "Link6");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][11], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][11], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][11], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][11], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][11], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][11], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][11], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][11], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][11], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][11], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][11],1);

	TDLaptopJanela[p][12] = CreatePlayerTextDraw(p,179.000000, 231.000000, "Link7");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][12], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][12], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][12], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][12], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][12], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][12], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][12], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][12], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][12], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][12], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][12],1);

	TDLaptopJanela[p][13] = CreatePlayerTextDraw(p,179.000000, 243.000000, "Link8");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][13], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][13], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][13], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][13], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][13], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][13], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][13], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][13], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][13], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][13], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][13],1);

	TDLaptopJanela[p][14] = CreatePlayerTextDraw(p,179.000000, 256.000000, "Link9");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][14], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][14], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][14], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][14], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][14], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][14], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][14], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][14], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][14], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][14], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][14],1);

	TDLaptopJanela[p][15] = CreatePlayerTextDraw(p,179.000000, 268.000000, "Link10");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][15], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][15], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][15], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][15], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][15], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][15], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][15], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][15], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][15], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][15], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][15],1);

	TDLaptopJanela[p][16] = CreatePlayerTextDraw(p,179.000000, 281.000000, "Link11");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][16], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][16], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][16], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][16], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][16], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][16], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][16], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][16], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][16], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][16], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][16],1);

	TDLaptopJanela[p][17] = CreatePlayerTextDraw(p,179.000000, 294.000000, "Link12");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][17], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][17], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][17], 0.189998, 0.899999);
	PlayerTextDrawColor(p,TDLaptopJanela[p][17], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][17], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][17], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][17], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][17], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][17], -256);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][17], 461.000000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][17],1);

	TDLaptopJanela[p][18] = CreatePlayerTextDraw(p,180.000000, 156.000000, "Meu Computador");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][18], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][18], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][18], 0.179996, 0.699998);
	PlayerTextDrawColor(p,TDLaptopJanela[p][18], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][18], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][18], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][18], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][18], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][18], -1);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][18], 460.500000, 3.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][18],1);

	TDLaptopJanela[p][19] = CreatePlayerTextDraw(p,452.000000, 156.000000, "Ir");
	PlayerTextDrawBackgroundColor(p,TDLaptopJanela[p][19], 255);
	PlayerTextDrawFont(p,TDLaptopJanela[p][19], 1);
	PlayerTextDrawLetterSize(p,TDLaptopJanela[p][19], 0.300000, 0.699998);
	PlayerTextDrawColor(p,TDLaptopJanela[p][19], 255);
	PlayerTextDrawSetOutline(p,TDLaptopJanela[p][19], 0);
	PlayerTextDrawSetProportional(p,TDLaptopJanela[p][19], 1);
	PlayerTextDrawSetShadow(p,TDLaptopJanela[p][19], 0);
	PlayerTextDrawUseBox(p,TDLaptopJanela[p][19], 1);
	PlayerTextDrawBoxColor(p,TDLaptopJanela[p][19], -1094795521);
	PlayerTextDrawTextSize(p,TDLaptopJanela[p][19], 460.500000, 10.000000);
	PlayerTextDrawSetSelectable(p,TDLaptopJanela[p][19],1);
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------
/*stock PlayerName(playerid)
{
	new nome[MAX_PLAYER_NAME]; GetPlayerName(playerid,nome,MAX_PLAYER_NAME);
	return nome;
}
//---------------------------------------------------------------------------------------------------------------------------------------
stock Profile(playerid)
{
	new profile[46];format(profile,sizeof(profile),"contas_rpg/%s.txt",PlayerName(playerid));
	return profile;
}*/
//----------------------------------------------------------------------------------------------------------------------------------------
stock Laptop(playerid)
{	
	new laptop[24]; format(laptop,24,"laptops/%s.txt", PlayerName(playerid));	
	return laptop;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock DestruirLaptop(playerid)
{
	for(new t=0;t<23;t++) PlayerTextDrawDestroy(playerid,TDLaptop[playerid][t]);
	for(new t=0;t<12;t++) PlayerTextDrawDestroy(playerid,TDLaptopMenu[playerid][t]);
	for(new t=0;t<20;t++) PlayerTextDrawDestroy(playerid,TDLaptopJanela[playerid][t]);
	PlayerTextDrawDestroy(playerid,TDLaptopWallpaper[playerid]);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock LaptopON(playerid) return LaptopInfo[playerid][ligado];
//----------------------------------------------------------------------------------------------------------------------------------------
stock LaptopLigado(playerid,bool:onoff)
{
	LaptopInfo[playerid][ligado]=onoff;
	ExibirLaptop(playerid);
	if(onoff==true)
	{
		PlayerTextDrawColor(playerid,TDLaptop[playerid][21], -16776961);
		PlayerTextDrawColor(playerid,TDLaptop[playerid][22], -16776961);		
		ExibirAreaDeTrabalho(playerid);
	}
	else{
		PlayerTextDrawColor(playerid,TDLaptop[playerid][21], 16711935);
		PlayerTextDrawColor(playerid,TDLaptop[playerid][22], 16711935);	
		OcultarMenu(playerid);
		OcultarJanela(playerid);
		OcultarOpcoesJanela(playerid);
		OcultarWallpaper(playerid);
	}
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PaginaEmail(playerid){
	OpcoesJanelaClicaveis(playerid,true,true,true,false,false,false,false,false,false,false,false);
	EditarCoresJanela(playerid,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x00C3FFFF);	
	EditarTituloJanela(playerid,"Email");
	new endereco[48]; format(endereco,48,"%s@brazucasrpg.com",PlayerName(playerid));
	EditarEnderecoJanela(playerid,endereco);
	EditarOpcoesJanela(playerid,"Caixa de Entrada","Escrever","Sair","_","_","_","_","_","_","_","_");
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",EMAIL);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirAreaDeTrabalho(playerid)
{
	OcultarJanela(playerid);
	ExibirWallpaper(playerid);
	ExibirMenuLaptop(playerid);
	SelectTextDraw(playerid, 0xFFFFFF3A); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirMenuLaptop(playerid){
	for(new t=0;t<12;t++) PlayerTextDrawShow(playerid,TDLaptopMenu[playerid][t]);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock OcultarMenu(playerid){ 
	for(new t=0;t<12;t++) PlayerTextDrawHide(playerid,TDLaptopMenu[playerid][t]); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EditarTituloJanela(playerid,titulo[]){ 
	if(strlen(titulo)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][2],titulo); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EditarEnderecoJanela(playerid,endereco[]){ 
	if(strlen(endereco)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][18],endereco); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirJanela(playerid){ 
	for(new t=0;t<7;t++) PlayerTextDrawShow(playerid,TDLaptopJanela[playerid][t]);
	PlayerTextDrawShow(playerid,TDLaptopJanela[playerid][18]); 
	PlayerTextDrawShow(playerid,TDLaptopJanela[playerid][19]); 	
	return 1;
}	
//----------------------------------------------------------------------------------------------------------------------------------------
stock FecharJanela(playerid)
{
	OcultarJanela(playerid);
	OcultarOpcoesJanela(playerid);
	DeixarSala(playerid);
	SetPVarInt(playerid,"Janela",DESKTOP);
	SelectTextDraw(playerid, 0xFFFFFF3A); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock OcultarJanela(playerid){ 
	for(new t=0;t<7;t++) PlayerTextDrawHide(playerid,TDLaptopJanela[playerid][t]);
	PlayerTextDrawHide(playerid,TDLaptopJanela[playerid][18]); 
	PlayerTextDrawHide(playerid,TDLaptopJanela[playerid][19]); 	
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirOpcoesJanela(playerid){ 
	for(new t=7;t<18;t++) PlayerTextDrawShow(playerid,TDLaptopJanela[playerid][t]); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock OcultarOpcoesJanela(playerid){ 
	for(new t=7;t<18;t++) PlayerTextDrawHide(playerid,TDLaptopJanela[playerid][t]); 
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EditarOpcoesJanela(playerid,opcao1[],opcao2[],opcao3[],opcao4[],opcao5[],opcao6[],opcao7[],opcao8[],opcao9[],opcao10[],opcao11[]){
	if(strlen(opcao1)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][7],opcao1),OpcoesJanelaClicavel(playerid,1,true);
	if(strlen(opcao2)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][8],opcao2),OpcoesJanelaClicavel(playerid,2,true);
	if(strlen(opcao3)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][9],opcao3),OpcoesJanelaClicavel(playerid,3,true);
	if(strlen(opcao4)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][10],opcao4),OpcoesJanelaClicavel(playerid,4,true);
	if(strlen(opcao5)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][11],opcao5),OpcoesJanelaClicavel(playerid,5,true);
	if(strlen(opcao6)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][12],opcao6),OpcoesJanelaClicavel(playerid,6,true);
	if(strlen(opcao7)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][13],opcao7),OpcoesJanelaClicavel(playerid,7,true);
	if(strlen(opcao8)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][14],opcao8),OpcoesJanelaClicavel(playerid,8,true);
	if(strlen(opcao9)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][15],opcao9),OpcoesJanelaClicavel(playerid,9,true);
	if(strlen(opcao10)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][16],opcao10),OpcoesJanelaClicavel(playerid,10,true);
	if(strlen(opcao11)) PlayerTextDrawSetString(playerid,TDLaptopJanela[playerid][17],opcao11),OpcoesJanelaClicavel(playerid,11,true);
	SelectTextDraw(playerid, 0x0000FF52);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock EditarCoresJanela(playerid,cor_opcao1,cor_opcao2,cor_opcao3,cor_opcao4,cor_opcao5,cor_opcao6,cor_opcao7,cor_opcao8,cor_opcao9,cor_opcao10,cor_opcao11,background){
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][7], cor_opcao1);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][8], cor_opcao2);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][9], cor_opcao3);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][10], cor_opcao4);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][11], cor_opcao5);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][12], cor_opcao6);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][13], cor_opcao7);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][14], cor_opcao8);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][15], cor_opcao9);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][16], cor_opcao10);
	PlayerTextDrawColor(playerid,TDLaptopJanela[playerid][17], cor_opcao11);
	PlayerTextDrawBoxColor(playerid,TDLaptopJanela[playerid][1], background);
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward QuandoJogadorSelecionaOpcao(playerid,opcaoid);
//----------------------------------------------------------------------------------------------------------------------------------------
stock OpcoesJanelaClicavel(playerid,opcaoid,bool:clicavel){
	switch(opcaoid){
		case 1: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][7],clicavel);
		case 2: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][8],clicavel);
		case 3: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][9],clicavel);
		case 4: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][10],clicavel);
		case 5: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][11],clicavel);
		case 6: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][12],clicavel);
		case 7: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][13],clicavel);
		case 8: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][14],clicavel);
		case 9: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][15],clicavel);
		case 10: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][16],clicavel);
		case 11: PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][17],clicavel);
	}
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock OpcoesJanelaClicaveis(playerid,bool:opcao1,bool:opcao2,bool:opcao3,bool:opcao4,bool:opcao5,bool:opcao6,bool:opcao7,bool:opcao8,bool:opcao9,bool:opcao10,bool:opcao11){
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][7],opcao1);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][8],opcao2);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][9],opcao3);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][10],opcao4);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][11],opcao5);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][12],opcao6);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][13],opcao7);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][14],opcao8);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][15],opcao9);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][16],opcao10);
	PlayerTextDrawSetSelectable(playerid,TDLaptopJanela[playerid][17],opcao11);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock AtualizarPapelDeParede(playerid,papelid,bool:show){
	if(show) PlayerTextDrawHide(playerid,TDLaptopWallpaper[playerid]);
	PlayerTextDrawSetString(playerid,TDLaptopWallpaper[playerid],LaptopWallpapers[GetPVarInt(playerid,"EscolhaJanela")]);
	LaptopInfo[playerid][papel_de_parede]=papelid;
	dini_IntSet(Laptop(playerid),"wallpaper",papelid);
	if(show) PlayerTextDrawShow(playerid,TDLaptopWallpaper[playerid]);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock AtualizarCorLaptop(playerid,corid,bool:show){
	new t = 0;
	while(t <= 20){
		switch(t){
			case 8..15,19,20:{
				if(show) PlayerTextDrawHide(playerid,TDLaptop[playerid][t]);
				PlayerTextDrawBoxColor(playerid,TDLaptop[playerid][t],LaptopCores[corid]);
				PlayerTextDrawColor(playerid,TDLaptop[playerid][t],LaptopCores[corid]);
				if(t!=20) PlayerTextDrawBackgroundColor(playerid,TDLaptop[playerid][t],LaptopCores[corid]);
				if(show) PlayerTextDrawShow(playerid,TDLaptop[playerid][t]);		
			}	
		}
		t++;
	}	
	LaptopInfo[playerid][cor_laptop]=corid;
	dini_IntSet(Laptop(playerid),"cor",corid);
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirWallpaper(playerid){ 
	PlayerTextDrawShow(playerid,TDLaptopWallpaper[playerid]); 
	return 1;
}	
//----------------------------------------------------------------------------------------------------------------------------------------
stock OcultarWallpaper(playerid){ 
	PlayerTextDrawHide(playerid,TDLaptopWallpaper[playerid]); 
	return 1;
}	
//----------------------------------------------------------------------------------------------------------------------------------------
stock ExibirLaptop(playerid){ 
	for(new t=0;t<23;t++) PlayerTextDrawShow(playerid,TDLaptop[playerid][t]);
	SelectTextDraw(playerid, 0xFFFFFF3A); 
	return 1;
}	
//----------------------------------------------------------------------------------------------------------------------------------------
stock OcultarLaptop(playerid){ 
	for(new t=0;t<23;t++) PlayerTextDrawHide(playerid,TDLaptop[playerid][t]);
	for(new t=0;t<12;t++) PlayerTextDrawHide(playerid,TDLaptopMenu[playerid][t]);
	for(new t=0;t<20;t++) PlayerTextDrawHide(playerid,TDLaptopJanela[playerid][t]);
	PlayerTextDrawHide(playerid,TDLaptopWallpaper[playerid]);
	CancelSelectTextDraw(playerid); 
	return 1;
}	
//----------------------------------------------------------------------------------------------------------------------------------------
stock AdquirirLaptop(playerid)
{
	dini_IntSet(Profile(playerid),"Laptop",dini_Int(Profile(playerid),"Laptop")+1);
	VerificarDesejoDe(playerid,4);
	if(!dini_Exists(Laptop(playerid))){		
		dini_Create(Laptop(playerid));		
	}
	CriarLaptop(playerid);
	CarregarLaptop(playerid);
	CriarCaixaPostal(playerid);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PerderLaptop(playerid)
{
	dini_IntSet(Profile(playerid),"Laptop",dini_Int(Profile(playerid),"Laptop")-1);
	if(fexist(Laptop(playerid))) fremove(Laptop(playerid));
	return 1;
}
//-------------------------------------------------------------------------------------------------------------------------------------
stock PossuiLaptop(playerid)
{
	if(fexist(Laptop(playerid))) return 1;
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PegarLaptop(playerid){
	if(!PossuiLaptop(playerid)) return 0;
	if(!LaptopInfo[playerid][em_maos]){
		DestruirLaptop(playerid);
		CriarLaptop(playerid);
		CarregarLaptop(playerid);
	}	
	ExibirLaptop(playerid);
	LaptopInfo[playerid][em_maos]=true;
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock GuardarLaptop(playerid){
	OcultarLaptop(playerid);
	DestruirLaptop(playerid);
	LaptopInfo[playerid][em_maos]=false;
	CancelSelectTextDraw(playerid);
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock LaptopEmMaos(playerid){
	return LaptopInfo[playerid][em_maos];
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZLaptop_OnPlayerChat(playerid, text[]);
public BRZLaptop_OnPlayerChat(playerid, text[]){
	switch(GetPVarInt(playerid,"Janela")){
		case SALA:{			
			new sala = PegarSala(playerid);
			sala = sala - 1;

			for(new t=0;t<9;t++){
				LinhasChat[sala][t] = LinhasChat[sala][t+1];
			}
			format(LinhasChat[sala][9],128,"%s:%s",PlayerName(playerid),text);
							
			for(new p=0;p<BRAZUCAS_PLAYERS;p++){
				if(!IsPlayerConnected(p)) continue;
				if(PegarSala(p) == (sala + 1) ){					
					new l = 0;
					for(new t=7;t<17;t++){
						PlayerTextDrawSetString(p,TDLaptopJanela[p][t],LinhasChat[sala][l++]);
						PlayerTextDrawShow(p,TDLaptopJanela[p][t]);
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock DeixarSala(playerid){
	if(PegarSala(playerid)!=0){
		new sala = PegarSala(playerid);
		sala = sala - 1;

		for(new t=0;t<9;t++){
			LinhasChat[sala][t] = LinhasChat[sala][t+1];
		}
		format(LinhasChat[sala][9],128,"%s saiu da sala",PlayerName(playerid));
							
		for(new p=0;p<BRAZUCAS_PLAYERS;p++){
			if(!IsPlayerConnected(p)) continue;
			if(PegarSala(p) == (sala + 1) ){					
				new l = 0;
				for(new t=7;t<17;t++){
					PlayerTextDrawSetString(p,TDLaptopJanela[p][t],LinhasChat[sala][l++]);
					PlayerTextDrawShow(p,TDLaptopJanela[p][t]);
				}
			}
		}
		SetarSala(playerid,0);
		return 1;
	}		
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZLaptop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
public BRZLaptop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PaginaBanco(playerid){
	EditarTituloJanela(playerid,"Bankline");	
	OpcoesJanelaClicaveis(playerid,true,true,true,true,true,true,false,false,false,false,false);
	EditarCoresJanela(playerid,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x007DFFFF);		
	EditarEnderecoJanela(playerid,"www.banco-brz.com");
	EditarOpcoesJanela(playerid,"Balanco Bancario","Extrato Bancario","Pagar Dividas","Transferencias","Investimento","Cambio","_","_","_","_","_");
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",BANKLINE);
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------	
stock PaginaChat(playerid){
	OpcoesJanelaClicaveis(playerid,true,true,true,true,true,false,false,false,false,false,false);
	EditarCoresJanela(playerid,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF7800FF);	
	EditarTituloJanela(playerid,"Bate-Papo");
	EditarEnderecoJanela(playerid,"www.chat-brz.com");
	EditarOpcoesJanela(playerid,"Sala 1","Sala 2","Sala 3","Sala 4","Sala 5","_","_","_","_","_","_");
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",CHAT);	
	return 1;
}	
//----------------------------------------------------------------------------------------------------------------------------------------
stock PaginaPrefeitura(playerid){
	EditarTituloJanela(playerid,"Prefeitura");
	EditarEnderecoJanela(playerid,"www.prefeitura-brz.com");
	EditarOpcoesJanela(playerid,"PREFEITURA DE LOS SANTOS","_","Enviar Curriculo","Pesquisa eleitoral","Ver tabela de arrecadacao","Ver dias de arrecadacao","Vagas disponiveis","Requisitos das profissoes","_","_","_");
	OpcoesJanelaClicaveis(playerid,false,false,true,true,true,true,true,true,false,false,false);
	EditarCoresJanela(playerid,0x00FF00FF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x003300FF);
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",PAGINA_PREFEITURA);
	//ShowPlayerDialog(playerid,47,DIALOG_STYLE_LIST,"Serviços disponíveis:","Enviar Curriculo\nPesquisa eleitoral\nVer tabela de arrecadacao\nVer dias de arrecadacao","Selecionar","Cancelar");
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PaginaShopping(playerid){
	EditarTituloJanela(playerid,"Shopping");
	EditarEnderecoJanela(playerid,"www.shopping-brz.com");
	EditarOpcoesJanela(playerid,"BRAZUCAS'SHOPPING","_","Itens diversos a venda","Veiculos a venda","Casas a venda","Propriedades a venda","_","_","_","_","_");
	OpcoesJanelaClicaveis(playerid,false,false,true,true,true,true,false,false,false,false,false);
	EditarCoresJanela(playerid,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF00E1FF);
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",PAGINA_SHOPPING);
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PaginaPolicia(playerid){
	EditarTituloJanela(playerid,"Policia");
	EditarEnderecoJanela(playerid,"www.policia-brz.com");
	EditarOpcoesJanela(playerid,"BRZ - DEPARTAMENTO DE POLICIA DE LOS SANTOS","-------------------------------------------------------------------------","Localizar suspeito","Chamar reforco","Procurados","Presos","Consultar multas","Veículos furtados","Outras denuncias","Ver ficha criminal","-------------------------------------------------------------------------");
	OpcoesJanelaClicaveis(playerid,false,false,true,true,true,true,true,true,true,true,false);
	EditarCoresJanela(playerid,0xF5FF00FF,0xF5FF00FF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xF5FF00FF,0x1E00FFFF);
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",PAGINA_POLICIA);
	//ShowPlayerDialog(playerid,COMPUTADOR_POLICIA_C,DIALOG_STYLE_LIST,"Departamento de Policia de Los Santos:","Localizar suspeito\nChamar reforço\nProcurados\nPresos\nConsultar multas\nVeículos furtados\nOutras denuncias\nVer ficha criminal","Selecionar","Cancelar");
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
stock PaginaDetran(playerid){
	EditarTituloJanela(playerid,"Detran");
	EditarEnderecoJanela(playerid,"www.detran-brz.com");
	EditarOpcoesJanela(playerid,"BRZ - DEPARTAMENTO DE POLICIA DE LOS SANTOS","-------------------------------------------------------------------------","Rastrear veiculo","Pesquisa por modelo","Localizar veiculos abandonados","Checar Documentacao","Pesquisa por Proprietario","Alvara de Taxi","Localizar veiculos com multa","_","-------------------------------------------------------------------------");
	OpcoesJanelaClicaveis(playerid,false,false,true,true,true,true,true,true,true,false,false);
	EditarCoresJanela(playerid,0x91FF00FF,0x91FF00FF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x91FF00FF,0x007673FF);
	ExibirJanela(playerid);
	ExibirOpcoesJanela(playerid);
	SetPVarInt(playerid,"Janela",PAGINA_DETRAN);
	//ShowPlayerDialog(playerid,42,DIALOG_STYLE_LIST,"Serviços disponíveis:","Rastrear veículo\nPesquisar veículos por modelo\nLocalizar veículos deixados nas vias públicas\nDocumentação de Veículos\nPesquisa por proprietário\nAdquirir alvará de taxi","Selecionar","Cancelar");
	return 1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZLaptop_OnPlayerClick(playerid,PlayerText:playertextid);
public BRZLaptop_OnPlayerClick(playerid,PlayerText:playertextid){
	if(LaptopInfo[playerid][em_maos]){
		//liga e desliga
		if(playertextid == TDLaptop[playerid][22]){
			if(GetPVarInt(playerid, "Janela") == PAGINA_FTP_INICIO) {
				FecharJanela(playerid);
				CallRemoteFunction("OnPlayerCloseFTP", "d", playerid);
			}
			LaptopLigado(playerid,!LaptopInfo[playerid][ligado]);
		}
		//botao fechar
		else if(playertextid == TDLaptopJanela[playerid][5]){
			if(GetPVarInt(playerid, "Janela") == PAGINA_FTP_INICIO)
				CallRemoteFunction("OnPlayerCloseFTP", "d", playerid);

			FecharJanela(playerid);
		}
		//msn
		else if(playertextid == TDLaptopMenu[playerid][2]){
			IniciarMSN(playerid);
		}
		//browser
		else if(playertextid == TDLaptopMenu[playerid][3]){
			EditarTituloJanela(playerid,"Brazuca's Browser");
			EditarEnderecoJanela(playerid,"about:blank");
			EditarCoresJanela(playerid,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0xFFFFFFFF);
			ExibirJanela(playerid);
			SetPVarInt(playerid,"Janela",BROWSER);
			SelectTextDraw(playerid,0x0000FF52);
		}
		//banco
		else if(playertextid == TDLaptopMenu[playerid][4]){
			PaginaBanco(playerid);
		}
		//chat
		else if(playertextid == TDLaptopMenu[playerid][5]){
			PaginaChat(playerid);
		}
		//email
		else if(playertextid == TDLaptopMenu[playerid][6]){
			PaginaEmail(playerid);		
		}
		//gps
		else if(playertextid == TDLaptopMenu[playerid][7]){
			IniciarGPS(playerid);
		}
		//shopping
		else if(playertextid == TDLaptopMenu[playerid][8]){
			PaginaShopping(playerid);
		}	
		//jogos
		else if(playertextid == TDLaptopMenu[playerid][9]){
		
		}	
		//player
		else if(playertextid == TDLaptopMenu[playerid][10]){
		
		}	
		//configuracoes
		else if(playertextid == TDLaptopMenu[playerid][11]){
			EditarTituloJanela(playerid,"Configuracoes");
			EditarEnderecoJanela(playerid,"Configuracoes");
			EditarCoresJanela(playerid,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0x000000FF,0xFFFFFFFF);
			EditarOpcoesJanela(playerid,"Papel de Parede","Cor","_","_","_","_","_","_","_","_","_");
			ExibirJanela(playerid);
			ExibirOpcoesJanela(playerid);
			SetPVarInt(playerid,"Janela",CONFIGURACOES);
		}
		else if(playertextid == TDLaptopJanela[playerid][18]){
			IniciarBrowser(playerid);
		}
		//opcoes das janelas
		else if(playertextid > TDLaptopJanela[playerid][6] && playertextid < TDLaptopJanela[playerid][18]){
			
			if(playertextid == TDLaptopJanela[playerid][7]) QuandoJogadorSelecionaOpcao(playerid,1);
			else if(playertextid == TDLaptopJanela[playerid][8]) QuandoJogadorSelecionaOpcao(playerid,2);
			else if(playertextid == TDLaptopJanela[playerid][9]) QuandoJogadorSelecionaOpcao(playerid,3);
			else if(playertextid == TDLaptopJanela[playerid][10]) QuandoJogadorSelecionaOpcao(playerid,4);
			else if(playertextid == TDLaptopJanela[playerid][11]) QuandoJogadorSelecionaOpcao(playerid,5);
			else if(playertextid == TDLaptopJanela[playerid][12]) QuandoJogadorSelecionaOpcao(playerid,6);
			else if(playertextid == TDLaptopJanela[playerid][13]) QuandoJogadorSelecionaOpcao(playerid,7);
			else if(playertextid == TDLaptopJanela[playerid][14]) QuandoJogadorSelecionaOpcao(playerid,8);
			else if(playertextid == TDLaptopJanela[playerid][15]) QuandoJogadorSelecionaOpcao(playerid,9);
			else if(playertextid == TDLaptopJanela[playerid][16]) QuandoJogadorSelecionaOpcao(playerid,10);
			else if(playertextid == TDLaptopJanela[playerid][17]) QuandoJogadorSelecionaOpcao(playerid,11);
				
			switch(GetPVarInt(playerid,"Janela")){
				/*
					if(playertextid == TDLaptopJanela[playerid][7]);
					else if(playertextid == TDLaptopJanela[playerid][8]);
					else if(playertextid == TDLaptopJanela[playerid][9]);
					else if(playertextid == TDLaptopJanela[playerid][10]);
					else if(playertextid == TDLaptopJanela[playerid][11]);
					else if(playertextid == TDLaptopJanela[playerid][12]);
					else if(playertextid == TDLaptopJanela[playerid][13]);
					else if(playertextid == TDLaptopJanela[playerid][14]);
					else if(playertextid == TDLaptopJanela[playerid][15]);
					else if(playertextid == TDLaptopJanela[playerid][16]);
					else if(playertextid == TDLaptopJanela[playerid][17]);
				*/
				case ESCREVENDO_EMAIL:{			
					if(playertextid == TDLaptopJanela[playerid][8])  EditarEmail(playerid,1);
					else if(playertextid == TDLaptopJanela[playerid][9])  EditarEmail(playerid,2);
					else if(playertextid == TDLaptopJanela[playerid][10]) EditarEmail(playerid,3);

					else if(playertextid == TDLaptopJanela[playerid][16]) ConcluirEmail(playerid);
					else if(playertextid == TDLaptopJanela[playerid][17]) PaginaEmail(playerid);		
				}
				case LENDO_EMAIL:{
					if(playertextid == TDLaptopJanela[playerid][16]) ApagarEmail(playerid,GetPVarInt(playerid,"LendoEmail"));
					else if(playertextid == TDLaptopJanela[playerid][17]) PaginaEmail(playerid);
				}
				case CAIXA_DE_ENTRADA:{				
					if(playertextid == TDLaptopJanela[playerid][7]) 	  LerEmail(PlayerName(playerid),playerid,1);
					else if(playertextid == TDLaptopJanela[playerid][8])  LerEmail(PlayerName(playerid),playerid,2);
					else if(playertextid == TDLaptopJanela[playerid][9])  LerEmail(PlayerName(playerid),playerid,3);
					else if(playertextid == TDLaptopJanela[playerid][10]) LerEmail(PlayerName(playerid),playerid,4);
					else if(playertextid == TDLaptopJanela[playerid][11]) LerEmail(PlayerName(playerid),playerid,5);
					else if(playertextid == TDLaptopJanela[playerid][12]) LerEmail(PlayerName(playerid),playerid,6);
					else if(playertextid == TDLaptopJanela[playerid][13]) LerEmail(PlayerName(playerid),playerid,7);
					else if(playertextid == TDLaptopJanela[playerid][14]) LerEmail(PlayerName(playerid),playerid,8);
					else if(playertextid == TDLaptopJanela[playerid][15]) LerEmail(PlayerName(playerid),playerid,9);
					else if(playertextid == TDLaptopJanela[playerid][16]) LerEmail(PlayerName(playerid),playerid,10);
					else if(playertextid == TDLaptopJanela[playerid][17]) PaginaEmail(playerid);			
				}
				case EMAIL:{
					if(playertextid == TDLaptopJanela[playerid][7]) ExibirEmails(playerid,playerid),SetPVarInt(playerid,"Janela",CAIXA_DE_ENTRADA);
					else if(playertextid == TDLaptopJanela[playerid][8]) ExibirEscreverEmail(playerid),SetPVarInt(playerid,"Janela",ESCREVENDO_EMAIL);
					else if(playertextid == TDLaptopJanela[playerid][9]) FecharJanela(playerid);
				}			
				case CHAT:{
					SetPVarInt(playerid,"Janela",SALA);
					EditarOpcoesJanela(playerid,"_","_","_","_","_","_","_","_","_","_","Sair da Sala");
					
					if(playertextid == TDLaptopJanela[playerid][7]) SetarSala(playerid,1),EditarEnderecoJanela(playerid,"Sala 1");
					else if(playertextid == TDLaptopJanela[playerid][8]) SetarSala(playerid,2),EditarEnderecoJanela(playerid,"Sala 2");
					else if(playertextid == TDLaptopJanela[playerid][9]) SetarSala(playerid,3),EditarEnderecoJanela(playerid,"Sala 3");
					else if(playertextid == TDLaptopJanela[playerid][10]) SetarSala(playerid,4),EditarEnderecoJanela(playerid,"Sala 4");
					else if(playertextid == TDLaptopJanela[playerid][11]) SetarSala(playerid,5),EditarEnderecoJanela(playerid,"Sala 5");
				}
				case SALA:{
					if(playertextid == TDLaptopJanela[playerid][17]) DeixarSala(playerid),EditarEnderecoJanela(playerid,"_"),EditarOpcoesJanela(playerid,"Sala 1","Sala 2","Sala 3","Sala 4","Sala 5","_","_","_","_","_","_");
				}			
				case CONFIGURACOES:{
					if(playertextid == TDLaptopJanela[playerid][7]) OcultarJanela(playerid), EditarOpcoesJanela(playerid,"Proxima","Anterior","Voltar","_","_","_","_","_","_","_","_"), SetPVarInt(playerid,"Janela",PLANO_DE_FUNDO);
					else if(playertextid == TDLaptopJanela[playerid][8]) EditarOpcoesJanela(playerid,"Proxima","Anterior","Voltar","_","_","_","_","_","_","_","_"), SetPVarInt(playerid,"Janela",CORES_LAPTOP);
				}
				case PLANO_DE_FUNDO:{
					if(playertextid == TDLaptopJanela[playerid][7]){
						SetPVarInt(playerid,"EscolhaJanela",GetPVarInt(playerid,"EscolhaJanela")+1);
						if(GetPVarInt(playerid,"EscolhaJanela")>(sizeof(LaptopWallpapers)-1)) SetPVarInt(playerid,"EscolhaJanela",0);
						AtualizarPapelDeParede(playerid,GetPVarInt(playerid,"EscolhaJanela"),true);
					}				
					else if(playertextid == TDLaptopJanela[playerid][8]){
						SetPVarInt(playerid,"EscolhaJanela",GetPVarInt(playerid,"EscolhaJanela")-1);
						if(GetPVarInt(playerid,"EscolhaJanela")<0) SetPVarInt(playerid,"EscolhaJanela",(sizeof(LaptopWallpapers)-1));
						AtualizarPapelDeParede(playerid,GetPVarInt(playerid,"EscolhaJanela"),true);
					}
					else if(playertextid == TDLaptopJanela[playerid][9]) ExibirJanela(playerid),EditarOpcoesJanela(playerid,"Papel de Parede","Cor","_","_","_","_","_","_","_","_","_"), SetPVarInt(playerid,"Janela",CONFIGURACOES);
				}
				case CORES_LAPTOP:{
					if(playertextid == TDLaptopJanela[playerid][7]){
						SetPVarInt(playerid,"EscolhaJanela",GetPVarInt(playerid,"EscolhaJanela")+1);
						if(GetPVarInt(playerid,"EscolhaJanela") > (sizeof(LaptopCores)-1) ) SetPVarInt(playerid,"EscolhaJanela",0);					
						AtualizarCorLaptop(playerid,GetPVarInt(playerid,"EscolhaJanela"),true);
					}				
					else if(playertextid == TDLaptopJanela[playerid][8]){
						SetPVarInt(playerid,"EscolhaJanela",GetPVarInt(playerid,"EscolhaJanela")-1);
						if(GetPVarInt(playerid,"EscolhaJanela")<0) SetPVarInt(playerid,"EscolhaJanela", (sizeof(LaptopCores)-1) );
						AtualizarCorLaptop(playerid,GetPVarInt(playerid,"EscolhaJanela"),true);				
					}
					else if(playertextid == TDLaptopJanela[playerid][9]) ExibirJanela(playerid),EditarOpcoesJanela(playerid,"Papel de Parede","Cor","_","_","_","_","_","_","_","_","_"), SetPVarInt(playerid,"Janela",CONFIGURACOES);
				}
				case BANKLINE:{
					if(playertextid == TDLaptopJanela[playerid][7]) MostrarBalanco(playerid,playerid);
					if(playertextid == TDLaptopJanela[playerid][8]) MostrarExtrato(PlayerName(playerid),playerid,10);
					if(playertextid == TDLaptopJanela[playerid][9]) IniciarPagarDividas(playerid);
					if(playertextid == TDLaptopJanela[playerid][10]) IniciarTransferencia(playerid);
					if(playertextid == TDLaptopJanela[playerid][11]) IniciarInvestimento(playerid);
					if(playertextid == TDLaptopJanela[playerid][12]) IniciarCambio(playerid);
				}
			}
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZLaptop_OnPlayerConnect(playerid);
public BRZLaptop_OnPlayerConnect(playerid){
	//CarregarLaptop(playerid);
}
//----------------------------------------------------------------------------------------------------------------------------------------
forward BRZLaptop_OnPlayerDisconnect(playerid);
public BRZLaptop_OnPlayerDisconnect(playerid){
	LaptopInfo[playerid][em_maos]=false;
}
//---------------------------------------------------------------------------------------------------------------------------------------
