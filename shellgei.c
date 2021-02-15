#ifndef _SHELLGEI_C
	#define _SHELLGEI_C
	int shell(char gotcmd[200], char *returnstr){
		FILE *fp;
		int i = 0, j;
		char finalcommand[800], buf[1000], *bunkatu[50], editedstr[500], originalcmd[200];
		//strtokの使用上元の文字列が変更されるため取得した文字列を別変数に格納する
		strcpy(originalcmd, gotcmd);
		//ダブルクォーテーションで分割
		while(1){
			if(i == 0){
				bunkatu[i] = strtok(originalcmd, "\"");
			}else if(bunkatu[i - 1] == NULL){
				i -= 2;
				break;
			}else{
				bunkatu[i] = strtok(NULL, "\"");
			}
			i++;
		}
		strcpy(editedstr, bunkatu[0]);
		//ダブルクォーテーションがあった場合エスケープして文字列を結合
		if(i != 0){
			for(j = 1; j <= i; j++){
				strcat(editedstr, "\\\"");
				strcat(editedstr, bunkatu[j]);
			}
			//分割数が奇数個だった場合最後のダブルクォーテーションを追加
			if(1 == i % 2){
				strcat(editedstr, "\\\"");
			}
		}
		//cmdコマンド作成
		sprintf(finalcommand, "(if not exist .\\linux mkdir .\\linux) & (if not exist .\\linux\\bash.exe %%WinDir%%\\system32\\curl.exe -s -o .\\linux\\bash.exe \"https://frippery.org/files/busybox/busybox64.exe\") & .\\linux\\bash.exe -c \"%s\"", editedstr);
		//コマンド実行
		fp = popen(finalcommand, "r");
		if(fp == NULL){
			return -1;
		}
		//一応ファイルポインタを最初に移動
		fseek(fp, 0, SEEK_SET);
		//出力結果読み出し
		while(1){
			if(fgets(buf, sizeof(buf), fp) == NULL){
				break;
			}
		}
		pclose(fp);
		//渡された文字配列にコピー
		strcpy(returnstr, buf);
		//返却値は文字列長
		return strlen(returnstr);
	}
#endif