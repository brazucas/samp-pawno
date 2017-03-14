#include <a_samp>
#include <dini>

new MaisRico;
new MaisProcurado;
new MaisViolento;
new MaisExperiente;
new MaisPresente;

stock ContaDe(playerid)
{
 new profile[128];
 format(profile,sizeof(profile),"contas/%s.txt",NomeDe(playerid));
 return profile;
}

stock NomeDe(playerid)
{
 new name[MAX_PLAYER_NAME];
 GetPlayerName(playerid, name, MAX_PLAYER_NAME);
 return name;
}

stock VerificarRank(playerid)
{
	new RRiqueza = dini_Int(ContaDe(playerid),"Fortuna");
	new RProcurado = dini_Int(ContaDe(playerid),"ProcuradoEx");
	new RAssassinatos = dini_Int(ContaDe(playerid),"Mortos");
	new RExperiencia = dini_Int(ContaDe(playerid),"Experiencia");
	new RConectado = dini_Int(ContaDe(playerid),"TempoConectado");
	
	if(RRiqueza>MaisRico) Rank(1,playerid,RRiqueza);
	if(RProcurado>MaisProcurado) Rank(2,playerid,RProcurado);
	if(RAssassinatos>MaisViolento) Rank(3,playerid,RAssassinatos);
	if(RExperiencia>MaisExperiente) Rank(4,playerid,RExperiencia);
	if(RConectado>MaisPresente) Rank(5,playerid,RConectado);
}

stock Rank(idrank,playerid,valor)
{
 if(dini_Exists("RankV.brz"))
 {
  switch(idrank)
  {
   case 1:
   {
 	dini_Set("RankV.brz","NomeMaisRico",NomeDe(playerid));
	dini_IntSet("RankV.brz","ValorMaisRico",valor);
   }
   case 2:
   {
 	dini_Set("RankV.brz","NomeMaisProcurado",NomeDe(playerid));
	dini_IntSet("RankV.brz","ValorMaisProcurado",valor);
   }
   case 3:
   {
 	dini_Set("RankV.brz","NomeMaisViolento",NomeDe(playerid));
	dini_IntSet("RankV.brz","ValorMaisViolento",valor);
   }
   case 4:
   {
 	dini_Set("RankV.brz","NomeMaisExperiente",NomeDe(playerid));
	dini_IntSet("RankV.brz","ValorMaisExperiente",valor);
   }
   case 5:
   {
 	dini_Set("RankV.brz","NomeMaisPresente",NomeDe(playerid));
	dini_IntSet("RankV.brz","ValorMaisPresente",valor);
   }
  }
 }
 CarregarRank();
}


stock CarregarRank()
{
 if(dini_Exists("RankV.brz"))
 {
  MaisRico =  dini_Int("RankV.brz","ValorMaisRico");
  MaisProcurado =  dini_Int("RankV.brz","ValorMaisProcurado");
  MaisViolento =  dini_Int("RankV.brz","ValorMaisViolento");
  MaisExperiente =  dini_Int("RankV.brz","ValorMaisExperiente");
  MaisPresente =  dini_Int("RankV.brz","ValorMaisPresente");
 }
}

stock AtualizarRank()
{
 print("Atualizando ranks...");
 fremove("RankListV.brz");
 new str[128],File:log=fopen("RankListV.brz",io_append);
 format(str,sizeof(str),"Jogador Mais Rico: %s Fortuna: R$ %d \r\n",dini_Get("RankV.brz","NomeMaisRico"),dini_Int("RankV.brz","ValorMaisRico"));fwrite(log,str);
 format(str,sizeof(str),"Jogador Mais Procurado: %s Níveis conseguidos: %d \r\n",dini_Get("RankV.brz","NomeMaisProcurado"),dini_Int("RankV.brz","ValorMaisProcurado"));fwrite(log,str);
 format(str,sizeof(str),"Jogador Mais Violento: %s Vítimas: %d \r\n",dini_Get("RankV.brz","NomeMaisViolento"),dini_Int("RankV.brz","ValorMaisViolento"));fwrite(log,str);
 format(str,sizeof(str),"Jogador Mais Experiente: %s Experiencia: %d \r\n",dini_Get("RankV.brz","NomeMaisExperiente"),dini_Int("RankV.brz","ValorMaisExperiente"));fwrite(log,str);
 format(str,sizeof(str),"Jogador Mais Presente: %s Tempo conectado: %dmin \r\n",dini_Get("RankV.brz","NomeMaisPresente"),dini_Int("RankV.brz","ValorMaisPresente"));fwrite(log,str);
 fclose(log);
}