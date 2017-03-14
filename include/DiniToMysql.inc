#include <a_mysql>

#if defined _dini_included
  #endinput
#endif

#define _dini_included
#define FAIL 		-1
#define MAX_STRING  128

#pragma library dutils

#include <dutils>
#include <a_samp>

stock GetPrimaryKey(table[]){
	new chave[24];
	if(strcmp(table,"contas_rpg",false)==0) 		format(chave,24,"NICK");
	else if(strcmp(table,"contas_mgs",false)==0) 	format(chave,24,"NOME");
	else if(strcmp(table,"postais",false)==0) 		format(chave,24,"NICK");
	else if(strcmp(table,"casas",false)==0) 		format(chave,24,"NUMERO");
	else if(strcmp(table,"veiculos",false)==0) 		format(chave,24,"PLACA");
	else if(strcmp(table,"propriedades",false)==0) 	format(chave,24,"NUMERO");
	else if(strcmp(table,"vagasProfissoes",false)==0) 	format(chave,24,"ID_PROF");
	//else if(strcmp(table,"propriedades",false)==0) 	format(chave,24,"MOCHILAS");
	else 											format(chave,24,"ID");
	return chave;
}

stock dini_Exists(filename[]) {
    if (fexist(filename)) return true;
	return false;

	/*
	//print("dini_Exists");
	if(explode(Escape, filename, "/")==FAIL){
		explode(Escape, filename, ".");
		Table = Escape[0];
		format(myQuery, sizeof(myQuery),"SELECT * FROM %s",Table);
	}
	else {
		Table = Escape[0];
		explode(Escape, Escape[1], ".");
		ID = Escape[0];
		format(myQuery, sizeof(myQuery),"SELECT * FROM %s WHERE %s='%s'",Table,GetPrimaryKey(Table),ID);
	}
	//printf("[DEBUG] %s",myQuery);
	//SendClientMessageToAll(0xFF000000, myQuery);
	mysql_query(myQuery);
	mysql_store_result();
	if(mysql_num_rows() > 0) {
		mysql_free_result();
		return true;
	}
	mysql_free_result();
	return false;
	*/
}

stock dini_Remove(filename[]) {
    new
		Escape[2][128],
		Table[128],
		ID[128]
	;

	new query[256];

	if (!fexist(filename)) return false;
	fremove(filename);

	if(explode(Escape, filename, "/")==FAIL){
		explode(Escape, filename, ".");
		Table = Escape[0];

		mysql_format(1, query, sizeof(query), "DELETE FROM %s", Table);
		mysql_pquery(1, query, "", "");
	}
	else {
		Table = Escape[0];
		explode(Escape, Escape[1], ".");
		ID = Escape[0];

		mysql_format(1, query, sizeof(query), "DELETE FROM %s WHERE %s = '%s'", Table,GetPrimaryKey(Table), ID);
		mysql_pquery(1, query, "", "");
	}

	return true;
}

stock dini_Create(filename[]) {
    new
		Escape[2][128],
		Table[128];
		//ID[128]
	//;

	new mysql[256];

    if(explode(Escape, filename, "/")==FAIL){
		explode(Escape, filename, ".");
		Table = Escape[0];
		mysql_format(1, mysql, sizeof(mysql), "CREATE TABLE %s (ID INT(3))", Table);
	} else {
		Table = Escape[0];

		mysql_format(1, mysql, sizeof(mysql),"INSERT INTO %s (%s) VALUES('%s')", Table,GetPrimaryKey(Table), Escape[1]);
		mysql_pquery(1, mysql, "", "");
	}

	new File:fhnd;
	if (fexist(filename)) return false;
	fhnd=fopen(filename,io_write);
	fclose(fhnd);

	return true;
}

stock dini_PRIVATE_ExtractKey(line[]) {
    //print("dini_PRIVATE_ExtractKey");
	new tmp[135];
	tmp[0]=0;
	if (strfind(line,"=",true)==-1) return tmp;
	set(tmp,strlower(ret_memcpy(line,0,strfind(line,"=",true))));
	return tmp;
}

stock dini_PRIVATE_ExtractValue(line[]) {
    //print("dini_PRIVATE_ExtractValue");
    new tmp[135];
    tmp[0]=0;
    if (strfind(line,"=",true)==-1) {
        return tmp;
    }
    set(tmp,ret_memcpy(line,strfind(line,"=",true)+1,strlen(line)));
    return tmp;
}

stock dini_Set(filename[],key[],value[]) {
    new
		Escape[2][128],
		Table[128],
		ID[128]
	;

	new query[256];

	//printf("XW_Hash: %s=%s", key, value);
    if(explode(Escape, filename, "/")==FAIL){
		explode(Escape, filename, ".");
		Table = Escape[0];

		mysql_format(1, query, sizeof(query),"SELECT %s FROM %s", key, Table);
		new Cache:mysqlFetch = mysql_query(1, query);

		if(cache_num_rows() <= 0){
			mysql_format(1, query, sizeof(query), "ALTER TABLE %s ADD COLUMN %s VARCHAR(50)", Table, key);
			mysql_pquery(1, query, "", "");
		}

		cache_delete(mysqlFetch);
	} else {
		Table = Escape[0];

		mysql_format(1, query, sizeof(query),"SELECT %s FROM %s", key, Table);
        new Cache:mysqlFetch = mysql_query(1, query);

		if(cache_num_rows() <= 0){
			mysql_format(1, query, sizeof(query), "ALTER TABLE %s ADD COLUMN %s VARCHAR(50)", Table, key);
			mysql_pquery(1, query, "", "");
		}

		cache_delete(mysqlFetch);

		explode(Escape, Escape[1], ".");
		ID = Escape[0];

		mysql_format(1, query, sizeof(query),"UPDATE %s SET %s = '%s' WHERE %s = '%s'", Table,key,value,GetPrimaryKey(Table),ID);
		mysql_pquery(1, query, "", "");
	}

	// --------------------------------------------------------------------------------------------------- //

    new File:fohnd, File:fwhnd;
	new bool:wasset=false;
	new tmpres[MAX_STRING+7];
	if (key[0]==0) return false; /* If we have no sign in key, it can't be set*/
	format(tmpres,sizeof(tmpres),"%s.part",filename);
	fohnd=fopen(filename,io_read);
	if (!fohnd) return false;
	fremove(tmpres);
	fwhnd=fopen(tmpres,io_write);
	//  if (!fwhnd) return false;
	while (fread(fohnd,tmpres)) {
		StripNewLine(tmpres);
		if ((!wasset)&&(equal(dini_PRIVATE_ExtractKey(tmpres),key,true))) {
			/* We've got what needs to be replaced! */
			format(tmpres,sizeof(tmpres),"%s=%s",key,value);
			wasset=true;
		}
		fwrite(fwhnd,tmpres);
		fwrite(fwhnd,"\r\n");
	}

	if (!wasset) {
		format(tmpres,sizeof(tmpres),"%s=%s",key,value);
		fwrite(fwhnd,tmpres);
		fwrite(fwhnd,"\r\n");
	}

	fclose(fohnd);
	fclose(fwhnd);

	format(tmpres,sizeof(tmpres),"%s.part",filename);
	if (fcopytextfile(tmpres,filename)) {
		return fremove(tmpres);
	}

	return false;
}

stock dini_IntSet(filename[],key[],value) {
	//print("dini_IntSet");
	new valuestring[135];
	format(valuestring,sizeof(valuestring),"%d",value);
	return dini_Set(filename,key,valuestring);
}

stock dini_Int(filename[],key[]) {
    //print("dini_Int");
   	return strval(dini_Get(filename,key));
}

stock dini_FloatSet(filename[],key[],Float:value) {
    //print("dini_FloatSet");
   	new valuestring[135];
   	format(valuestring,sizeof(valuestring),"%f",value);
   	return dini_Set(filename,key,valuestring);
}

stock Float:dini_Float(filename[],key[]) {
    //print("dini_Float");
   	return floatstr(dini_Get(filename,key));
}

stock  dini_Bool(filename[],key[]) {
    //print("dini_Bool");
   	return strval(dini_Get(filename,key));
}

stock dini_BoolSet(filename[],key[],value) {
    //print("dini_BoolSet");
   	new valuestring[135];
   	format(valuestring,sizeof(valuestring),"%d",value);
   	return dini_Set(filename,key,valuestring);
}

stock dini_Unset(filename[],key[]) {
    //print("dini_Unset");
	dini_Set(filename,key,"");
	return false;
}

stock dini_Get(filename[],key[]) {
	new File:fohnd;
	new tmpres[135];
	new tmpres2[135];
	tmpres[0]=0;
	fohnd=fopen(filename,io_read);
	if (!fohnd) return tmpres;
	while (fread(fohnd,tmpres)) {
		StripNewLine(tmpres);
		if (equal(dini_PRIVATE_ExtractKey(tmpres),key,true)) {
			/* We've got what we need */
			tmpres2[0]=0;
			strcat(tmpres2,dini_PRIVATE_ExtractValue(tmpres));
			fclose(fohnd);
			return tmpres2;
		}
	}
	fclose(fohnd);
	return tmpres;
}


stock dini_Isset(filename[],key[]) {
	new File:fohnd;
	new tmpres[135];
	fohnd=fopen(filename,io_read);
	if (!fohnd) return false;
	while (fread(fohnd,tmpres)) {
		StripNewLine(tmpres);
		if (equal(dini_PRIVATE_ExtractKey(tmpres),key,true)) {
			/* We've got what we need */
			fclose(fohnd);
			return true;
		}
	}
	fclose(fohnd);
	return false;
}

ret_memcpy(source[],index=0,numbytes) {
	new tmp[135];
	new i=0;
	tmp[0]=0;
	if (index>=strlen(source)) return tmp;
	if (numbytes+index>=strlen(source)) numbytes=strlen(source)-index;
	if (numbytes<=0) return tmp;
	for (i=index;i<numbytes+index;i++) {
		tmp[i-index]=source[i];
		if (source[i]==0) return tmp;
	}
	tmp[numbytes]=0;
	return tmp;
}

stock RemoveLineFromFile(line[],filename[]){
    //print("RemoveLineFromFile");
	new aLineFromTheFile[135];
	new aLineToRemove[135];
	format(aLineToRemove,135,"%s\r\n",line);
	new File:f = fopen(filename, io_read);
	new File:temp = fopen("temp.txt", io_write);
	while (fread(f, aLineFromTheFile)){
		if(strcmp(aLineFromTheFile,aLineToRemove,true)==0){
	        continue;
	    }
	    fwrite(temp, aLineFromTheFile);
	}
	fclose(f);
	fclose(temp);
	f = fopen(filename, io_write);
	temp = fopen("temp.txt", io_read);
	while (fread(temp, aLineFromTheFile))
	{
	    fwrite(f, aLineFromTheFile);
	}
	fclose(f);
	fclose(temp);
	fremove("temp.txt");
}