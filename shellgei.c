#ifndef _SHELL_C
	#define _SHELL_C
	int shellgei(char *origincmd, char *returnstr){
		FILE *fp, *cmd;
		char buf[1000];
		//カレントディレクトリに"shellgei"フォルダを作成
		system("if not exist .\\shellgei (mkdir .\\shellgei)");
		//"shellgei"フォルダ内に"shellgei.sh"ファイルを作成
		fp = fopen(".\\shellgei\\shellgei.sh", "w");
		//失敗した場合終了
		if(fp == NULL){
			return -1;
		}
		//ファイル内にコマンドを書き込み
		fprintf(fp, origincmd);
		fclose(fp);
		//"shellgei"フォルダ内に"bash.exe"をダウンロード
		system("if not exist .\\shellgei\\bash.exe (%Windir%\\system32\\curl.exe -o .\\shellgei\\bash.exe \"https://frippery.org/files/busybox/busybox64.exe\")");
		//ファイルを渡してコマンドを実行
		fp = popen(".\\shellgei\\bash.exe .\\shellgei\\shellgei.sh", "r");
		if(fp == NULL){
			return -1;
		}
		strcpy(returnstr, "");
		while(1){
			if(fgets(buf, sizeof(buf), fp) == NULL){
				break;
			}
			strcat(returnstr, buf);
		}
		pclose(fp);
		//"shellgei"フォルダを削除(必要ないかも)
		//system("del .\\shellgei /Q");
		//返り値は文字長
		return strlen(returnstr);
	}
#endif