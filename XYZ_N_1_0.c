#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
//全局变量
typedef struct{
    char c[1000];
    int n;
    int m[1000];
}result;
result SAS={"未测试",0,0};
result BDI={"未测试",0,0};
result MBTI={"未测试",0,0};

//预定义函数
void colorful_printf(WORD color, const char* format, ...);//彩色字体
void dialog();//更新日志//
void output();//导入导出//
result SAStest();//焦虑自评量表
result BDItest();//抑郁自评量表
result MBTItest();//简版MBTI人格量表

//函数主体
void main() {
	system("chcp 65001 & cls");//设置UTF-8编码并清屏
	while (1) {
		system("cls");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"★");
		printf(" 小叶子的心理评测小程序 ");
        colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"★\n\n");

		printf("101.焦虑自评量表(SAS)            -上次得分:%d/%s\n", SAS.n, SAS.c); 
		printf("102.抑郁自评量表(BDI)            -上次得分:%d/%s\n", BDI.n, BDI.c);
        printf("103.简版MBTI人格量表             -上次结果:%s\n",MBTI.c);

		printf("\n");
		printf("1.导出结果\n");
        printf("2.更新日志\n");
		printf("3.退出程序\n");
		printf("\n输入");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"对应数字序号");
		printf("启动相应功能:");
		int n;
		rewind(stdin);
		if (scanf("%d", &n) == 0) {
			printf("\n输入有误,请1秒后重试\n");
			Sleep(800);
			continue;
		}
		switch (n) {
			case 101 :
                SAS=SAStest();
				continue;
			case 102 :
                BDI=BDItest();
				continue;
            case 103 :
                MBTI=MBTItest();
                continue;
			case 1 :
                output();
				continue;
			case 2 :
                dialog();
				continue;
			case 3 :
				exit(1);
			default :
				printf("\n输入有误,请1秒后重试\n");
				Sleep(800);
				continue;
		}
	}
}
void colorful_printf(WORD color, const char* format, ...) {
    //获取控制台输出句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //保存原来的文本属性
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    //设置新的文本属性
    SetConsoleTextAttribute(hConsole, color);
    //打印格式化字符串
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    //恢复原来的文本属性
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}
void output() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    while (1) {
		system("cls");
        colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"★");
		printf(" 小叶子的心理评测小程序 ");
        colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"★\n\n");
		printf("1.导出本次结果到");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]\n");
		printf("2.从");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]");
		printf("导入本地结果\n");
        printf("3.记录结果和时间到");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]");
        printf("日志中\n");
		printf("4.记录结果和时间到");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[D盘根目录]");
        printf("日志中\n");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n5.返回上一级\n");
		printf("\n输入");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"对应数字序号");
		printf("启动相应功能:");
		int n;
		rewind(stdin);
		if (scanf("%d", &n) == 0) {
			colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n输入有误,请1秒后重试\n");
			Sleep(800);
			continue;
		}
		switch (n) {
			case 1 :
                FILE *fp1 = NULL;
                fp1 = fopen("SAVE_XYZ.txt", "w+");

                fprintf(fp1, "1.焦虑水平测试-上次得分:%d/%s\n", SAS.n, SAS.c);
                fprintf(fp1, "2.抑郁水平测试-上次得分:%d/%s\n", BDI.n, BDI.c);
                fprintf(fp1, "3.简版MBTI人格量表-上次结果:%s\n",MBTI.c);

                fprintf(fp1, "保存时间:%d-%02d-%02d %02d:%02d:%02d\n",
                        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                        tm.tm_hour, tm.tm_min, tm.tm_sec);
                fclose(fp1);
                system("cls");
                printf("本次结果已保存到");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]");
                printf("的");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"SAVE_XYZ.txt");
                printf("文件中\n");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
                getch();
				return;
			case 2 :
				FILE *fp2 = NULL;
                fp2 = fopen("SAVE_XYZ.txt", "r");

                char buff1[200];fgets(buff1, 200, (FILE *)fp2);sscanf(buff1, "1.焦虑水平测试-上次得分:%d/%s\n", &SAS.n, &SAS.c);
                char buff2[200];fgets(buff2, 200, (FILE *)fp2);sscanf(buff2, "2.抑郁水平测试-上次得分:%d/%s\n", &BDI.n, &BDI.c);
                char buff3[200];fgets(buff3, 200, (FILE *)fp2);sscanf(buff2, "3.简版MBTI人格量表-上次结果:%s\n",&MBTI.c);

                fclose(fp2);
                system("cls");
                printf("已从");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]");
                printf("的");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"SAVE_XYZ.txt");
                printf("文件中读取上次保存的结果\n");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
                getch();
				return;
			case 3 :
                FILE *fp3 = NULL;
                fp3 = fopen("DIARY_XYZ.txt", "a+");

                fprintf(fp3, "1.焦虑水平测试-上次得分:%d/%s\n", SAS.n, SAS.c);
                fprintf(fp3, "2.抑郁水平测试-上次得分:%d/%s\n", BDI.n, BDI.c);
                fprintf(fp3, "3.简版MBTI人格量表-上次结果:%s\n",MBTI.c);
                
                fprintf(fp3, "保存时间:%d-%02d-%02d %02d:%02d:%02d\n\n",
                        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                        tm.tm_hour, tm.tm_min, tm.tm_sec);
                fclose(fp3);
                system("cls");
                printf("本次结果已添加在");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]");
                printf("的");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"DIARY_XYZ.txt");
                printf("文件中\n");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
                getch();
				return;
			case 4 :
                FILE *fp4 = NULL;
                fp4 = fopen("D:\\DIARY_XYZ.txt", "a+");

                fprintf(fp4, "1.焦虑水平测试-上次得分:%d/%s\n", SAS.n, SAS.c);
                fprintf(fp4, "2.抑郁水平测试-上次得分:%d/%s\n", BDI.n, BDI.c);
                fprintf(fp4, "3.简版MBTI人格量表-上次结果:%s\n",MBTI.c);
                
                fprintf(fp4, "保存时间:%d-%02d-%02d %02d:%02d:%02d\n\n",
                        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                        tm.tm_hour, tm.tm_min, tm.tm_sec);
                fclose(fp4);
                system("cls");
                printf("本次结果已添加在");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"[当前目录]");
                printf("的");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"DIARY_XYZ.txt");
                printf("文件中\n");
                colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
                getch();
				return;
			case 5 :
				return;
			default :
			    colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n输入有误,请1秒后重试\n");
				Sleep(800);
				continue;
		}
	}
}
void dialog() {
    system("cls");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"★");
	printf(" 小叶子的心理评测小程序(1.0) ");//记得改版本号
    colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"★\n\n");
	printf("量表结果仅供参考,如有疑问请查阅相关文献\n");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n更新日志:\n");

	printf("1.0 2023.8.2 新代码首个版本,包含SAS、BDI、简版MBTI三个量表\n");

	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键返回");
	getch();
}
result SAStest(){
    result out={"未测试",0,0};
    system("cls");
	printf("焦虑自评量表(self-rating anxiety scale)由w.k.zung于1971年编制\n");
	printf("用于评出有焦虑症状的个体的主观感受\n");
	printf("下面有20条文字,请仔细阅读每一条,把意思弄明白\n");
	printf("然后按照自己最近一周以来的实际情况进行选择\n\n");
	Sleep(1000);
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"请理性看待结果,存在焦虑症状不等于患了焦虑症\n");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"如有需要,请务必到医院诊断,并以医院诊断结果为准\n");
	Sleep(1000);
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
	getch();
	int i;
	for (i = 1; i <= 20; i++) {
		switch (i) {
			case 1 :
				printf("\n1.觉得比平常容易紧张和着急(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 2 :
				printf("\n2.无缘无故地感到害怕(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 3 :
				printf("\n3.容易心里烦乱或觉得惊恐(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 4 :
				printf("\n4.觉得可能要发疯(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 5 :
				printf("\n5.觉得一切都很好,也不会发生什么不幸(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 6 :
				printf("\n6.手脚发抖打颤(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 7 :
				printf("\n7.因为头痛、头颈痛和背痛而苦恼(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 8 :
				printf("\n8.感觉容易衰弱和疲乏(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 9 :
				printf("\n9.觉得心平气和,并且容易安静地坐着(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 10 :
				printf("\n10.觉得心跳得很快(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 11 :
				printf("\n11.因为一阵阵头晕而苦恼(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 12 :
				printf("\n12.有晕倒发作,或觉得要晕倒似的(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 13 :
				printf("\n13.吸气呼气都感到很容易(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 14 :
				printf("\n14.手脚麻木和刺痛(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 15 :
				printf("\n15.因为胃痛和消化不良而苦恼(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 16 :
				printf("\n16.常常要小便(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 17 :
				printf("\n17.手常常是干燥温暖的(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 18 :
				printf("\n18.脸红发热(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 19 :
				printf("\n19.容易入睡并且睡得很好(1.很少 2.有时 3.经常 4.持续)\n");
				break;
			case 20 :
				printf("\n20.做噩梦(1.很少 2.有时 3.经常 4.持续)\n");
				break;
		}
		rewind(stdin);
		int n;
		if (scanf("%d", &n) == 0) { //输入字符也会报错了
			printf("\n输入有误,本次评测作废");
			colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
			Sleep(1500);
			return(SAS);
		}
		if (i == 5 || i == 9 || i == 13 || i == 17 || i == 19) {
			switch (n) {
				case 1 :
					out.n += 4;
					break;
				case 2 :
					out.n += 3;
					break;
				case 3 :
					out.n += 2;
					break;
				case 4 :
					out.n += 1;
					break;
				default :
					printf("\n输入有误,本次评测作废");
				    colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
					Sleep(1500);
					return(SAS);
			}
		} else {
			switch (n) {
				case 1 :
					out.n += 1;
					break;
				case 2 :
					out.n += 2;
					break;
				case 3 :
					out.n += 3;
					break;
				case 4 :
					out.n += 4;
					break;
				default :
					printf("\n输入有误,本次评测作废");
				    colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
					Sleep(1500);
					return(SAS);
			}
		}

	}
	if (out.n <= 49) {
		strcpy(out.c, "正常");
	}
	if (out.n >= 50 && out.n <= 59) {
		strcpy(out.c, "轻度焦虑症状");
	}
	if (out.n >= 60 && out.n <= 69) {
		strcpy(out.c, "中度焦虑症状");
	}
	if (out.n >= 69) {
		strcpy(out.c, "重度焦虑症状");
	}
	printf("\n测试完成,请返回查看结果");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(按任意键返回)\n");
	getch();
    return(out);
}
result BDItest(){
    result out={"未测试",0,0};
    system("cls");
	printf("贝克抑郁自评量表(Beck Depression Inventory)\n");
	printf("由美国心理学家BeckAT编制于20世纪60年代\n");
	printf("被广泛应于临床流行病学调查\n");
	printf("依据总分,能明白无误地了解自己是否有抑郁,抑郁的程度如何\n\n");
	Sleep(1000);
	printf("在开始评定前,保持自己的状态,不受任何人影响的自我评定\n");
	printf("评定的时间,是“现在”或者是“最近一个星期”的实际感觉\n");
	printf("一般而言, 本量表不适合于文盲和低教育人群\n");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"请理性看待结果,存在抑郁症状不等于患了抑郁症\n");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"如果得分超过8分,建议到医院进行专业评估\n");
	Sleep(1000);
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
	getch();
	int i;
	for (i = 1; i <= 13; i++) {
		switch (i) {
			case 1 :
				printf("\n以下情况最符合你的是");
				printf("\n1.我不感到忧郁或沮丧\n2.我感到忧郁或沮丧\n3.我整天忧郁,无法摆脱\n4.我十分忧郁,已经承受不住\n");
				break;
			case 2 :
				printf("\n你对未来抱有什么态度");
				printf("\n1.我对未来并不感到悲观失望\n2.我感到前途不太乐观\n3.我感到我对前途不抱希望\n4.我感到今后毫无希望,不可能有所好转\n");
				break;
			case 3 :
				printf("\n你是如何看待失败的感觉");
				printf("\n1.我并无失败的感觉\n2.我觉得和大多数人相比我是失败的\n3.回顾我的一生,我觉得那是一连串的失败\n4.我觉得我是个彻底失败的人\n");
				break;
			case 4 :
				printf("\n你对生活的满意度如何");
				printf("\n1.我并不觉得我有什么不满意\n2.我觉得我不能像平时那样享受生活\n3.任何事情都不能使我感到满意一些\n4.我对所有的事情都不满意\n");
				break;
			case 5 :
				printf("\n你的内疚感有多深");
				printf("\n1.我没有特殊的内疚感\n2.我有时感到内疚或觉得自己没价值\n3.我感到非常内疚\n4.我觉得自己非常坏,一文不值\n");
				break;
			case 6 :
				printf("\n你是否会对自己感到失望");
				printf("\n1.我没有对自己感到失望\n2.我对自己感到失望\n3.我讨厌自己\n4.我憎恨自己\n");
				break;
			case 7 :
				printf("\n你会有想要伤害自己的想法吗");
				printf("\n1.我没有要伤害自己的想法\n2.我感到还是死掉的好\n3.我考虑过自杀\n4.如果有机会,我还会杀了自己\n");
				break;
			case 8 :
				printf("\n你是否失去与他人交往的兴趣");
				printf("\n1.我没失去和他人交往的兴趣\n2.和平时相比,我和他人交往的兴趣有所减退\n3.我已失去大部分和人交往的兴趣,我对他们没有感情\n4.我对他人全无兴趣,也完全不理睬别人\n");
				break;
			case 9 :
				printf("\n对你来说,做决定是否困难");
				printf("\n1.我能像平时一样做出决断\n2.我尝试避免做决定\n3.对我而言,做出决断十分困难\n4.我无法做出任何决断\n");
				break;
			case 10 :
				printf("\n与过去相比,你是否对你的形象不自信");
				printf("\n1.我觉得我的形象一点也不比过去糟\n2.我担心我看起来老了,不吸引人了\n3.我觉得我的外表肯定变了,变得不具吸引力\n4.我觉得我的形象丑陋不堪且讨人厌\n");
				break;
			case 11 :
				printf("\n你对工作抱有何种态度");
				printf("\n1.我能像平时那样工作\n2.我做事时,要额外地努力才能开始\n3.我必须努力迫使自己,方能干事\n4.我完全不能做事情\n");
				break;
			case 12 :
				printf("\n和以往相比,你是否会很容易就感到疲倦");
				printf("\n1.和以往相比,我并不容易疲倦\n2.我比过去容易觉得疲倦\n3.我做任何事都感到疲倦\n4.我太易疲倦了,不能干任何事\n");
				break;
			case 13 :
				printf("\n与过去相比,你的胃口如何");
				printf("\n1.我的胃口不比过去差\n2.我的胃口没有过去那样好\n3.现在我的胃口比过去差多了\n4.我一点食欲都没有\n");
				break;
		}
		rewind(stdin);
		int n;
		if (scanf("%d", &n) == 0) {
			printf("\n输入有误,本次评测作废");
			colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
			Sleep(1500);
			return (BDI);
		}
		switch (n) {
			case 1 :
				break;
			case 2 :
				out.n += 1;
				break;
			case 3 :
				out.n += 2;
				break;
			case 4 :
				out.n += 3;
				break;
			default :
				printf("\n输入有误,本次评测作废");
				colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
				Sleep(1500);
				return (BDI);
		}
	}
	if (out.n <= 4) {
		strcpy(out.c, "正常");
	}
	if (out.n >= 5 && out.n <= 7) {
		strcpy(out.c, "轻度抑郁症状");
	}
	if (out.n >= 8 && out.n <= 15) {
		strcpy(out.c, "中度抑郁症状");
	}
	if (out.n >= 16) {
		strcpy(out.c, "重度抑郁症状");
	}
	printf("\n测试完成,请返回查看结果");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(按任意键返回)\n");
	getch();
    return(out);
}
result MBTItest(){
    result out={"未测试",0,0};
    system("cls");
	printf("请选择您想执行的功能:\n\n");
	printf("1.通过网页进行完整版测试\n");
	printf("2.查看各性格类型详细解析\n");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"3.进行简版MBTI人格测试\n");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n4.返回上一级\n");
	printf("\n输入");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"对应数字序号");
	printf("启动相应功能:");
	int m;
	if (scanf("%d", &m) == 0) {
		printf("\n输入有误");
		colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
		Sleep(1500);
		return(MBTI);
	}
	switch(m){
		case 1 :system("start https://www.16personalities.com/ch/%E4%BA%BA%E6%A0%BC%E6%B5%8B%E8%AF%95");
		        return(MBTI);
		case 2 :system("start https://www.16personalities.com/ch/%E7%B1%BB%E5%9E%8B%E6%8F%8F%E8%BF%B0");
		        return(MBTI);
		case 3 :system("cls");
		        break;
		case 4 :return(MBTI);
		default:printf("\n输入有误");
		        colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
		        Sleep(1500);
		        return(MBTI);
	}
	Sleep(100);
	printf("本量表为");
    colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"简版");
    printf("十六型人格(MBTI)量表,仅28题\n");
	printf("请根据您的实际情况通过输入数字选择选项1或选项2\n\n");
    Sleep(1000);
	printf("MBTI量表本身信效度不佳,本量表又是简版\n");
    printf("请理性看待结果,四个字母定义不了您的人格\n");
	Sleep(1000);
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"\n按任意键继续\n");
	getch();
	int i;
	for (i = 1; i <= 28; i++) {
		switch (i) {
			case 1 :
			printf("\n我倾向从何处得到力量:\n1.别人\n2.我自己的想法\n");
			break;
			case 2 :
			printf("\n当我参加一个社交聚会时,我倾向于:\n1.在夜色很深时,只要我开始投入,也许就是最晚离开的那一个\n2.在夜晚开始的时候,我就疲倦了并且想回家\n");
			break;
			case 3 :
			printf("\n下列哪一种听起来比较吸引人:\n1.与我的爱人到有很多人且社交活动频繁的地方\n2.待在家中与我的爱人做一些特别的事情\n  例如说观赏一部有趣的视频带并享用我最爱的食物\n");
			break;
			case 4 :
			printf("\n在约会中,我通常:\n1.整体来说蛮健谈的\n2.较安静且保留,直到我觉得舒服\n");
			break;
			case 5 :
			printf("\n过去,我结交大多数朋友或爱人的方式是:\n1.通过社交聚会,酒吧夜总会,工作和学习会议等\n2.通过朋友或家人介绍,别人主动来加微信,交友软件等\n");
			break;
			case 6 :
			printf("\n我更倾向拥有:\n1.很多认识的人和亲密的朋友\n2.几个很亲密的朋友\n");
			break;
			case 7 :
			printf("\n我的朋友或爱人对我说过:\n1.你难道不可以安静一点吗\n2.你可以从自己的世界里出来一下吗\n");
			break;
			case 8 :
			printf("\n我脑中更多的存在:\n1.我对有可能发生之事的想象和期望\n2.我对目前状况实际认知\n");
			break;
			case 9 :
			printf("\n我倾向于相信:\n1.我的直觉\n2.我的观察和经验\n");
			break;
			case 10 :
			printf("\n当我置身于一段关系中时,我倾向于认为:\n1.它永远有进步空间\n2.现在这样就是最好的\n");
			break;
			case 11 :
			printf("\n在一场放松的约会中,我倾向于谈论:\n1.未来的可能性\n2.现实的生活和事物\n");
			break;
			case 12 :
			printf("\n我是这种人:\n1.喜欢先整体把握\n2.喜欢从细节着手\n");
			break;
			case 13 :
			printf("\n如果可以选择,我会:\n1.活在我的想象里\n2.还是活在现实中\n");
			break;
			case 14 :
			printf("\n关于即将到来的约会,我更倾向于:\n1.想象一大堆即将在约会中发生的事\n2.只是报以期待,让它自然发生\n");
			break;
			case 15 :
			printf("\n我倾向于如此做决定:\n1.首先依我的心情\n2.首先依我的逻辑\n");
			break;
			case 16 :
			printf("\n我能更好察觉到:\n1.别人需要情感上的支持\n2.别人不合逻辑的地方\n");
			break;
			case 17 :
			printf("\n当和某人分手时:\n1.我深陷其中,很难抽身而出\n2.我只要下定决心,就可以甩掉过去的影子\n");
			break;
			case 18 :
			printf("\n与别人交往时,我更在意:\n1.情感上的兼容性:表达感情和敏锐捕捉对方的需求\n2.智慧上的兼容性:沟通重要的想法,客观地讨论和辩论事情\n");
			break;
			case 19 :
			printf("\n当我不同意我情人的想法时:\n1.我尽可能地避免伤害对方的感受,若是会对对方造成伤害的话,我就不会说\n2.我通常毫无保留地说话,并且对我的情人直言直语,因为对的就是对的\n");
			break;
			case 20 :
			printf("\n认识我的人倾向形容我为:\n1.富有感情而敏感\n2.富有逻辑而明确\n");
			break;
			case 21 :
			printf("\n我把大部分和别人的相遇视为:\n1.友善且重要的\n2.必要或有目的的\n");
			break;
			case 22 :
			printf("\n若我有时间和金钱,我的朋友邀请我到国外度假,并且在一天前才通知,我会:\n1.看看有没有时间\n2.立即开始收拾行李\n");
			break;
			case 23 :
			printf("\n如果我的约会对象迟到了,我会:\n1.很不高兴\n2.无所谓\n");
			break;
			case 24 :
			printf("\n我更偏向于:\n1.精心计划的旅行\n2.说走就走的旅行\n");
			break;
			case 25 :
			printf("\n我的生活遵循着:\n1.日程表和计划\n2.自然而然和弹性\n");
			break;
			case 26 :
			printf("\n下面哪一项更为常见:\n1.我准时出席而其他人迟到\n2.大多数人都准时出席而我迟到\n");
			break;
			case 27 :
			printf("\n我更喜欢这样的人:\n1.下定决心并且做出最后肯定的结论\n2.开放性地选择并且持续收集信息\n");
			break;
			case 28 :
			printf("\n我是这种类型的人:\n1.喜欢在一个时间里专心于一件事情直到完成\n2.享受同时进行好几件事情\n");
			break;
		}
		rewind(stdin);
		int n;
		if (scanf("%d", &n) == 0) {
			printf("\n输入有误,本次评测作废");
			colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
			Sleep(1500);
			return (MBTI);
		}
		if (i <= 7) {
			switch (n) {
				case 1 :
				    out.m[0]+=1;
					break;
				case 2 :
					out.m[1]+=1;
					break;
				default :
					printf("\n输入有误,本次评测作废");
					colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
					Sleep(1500);
					return (MBTI);
			}
		} 
		else if(i >= 8 && i <= 14){
			switch (n) {
				case 1 :
				    out.m[2]+=1;
					break;
				case 2 :
					out.m[3]+=1;
					break;
				default :
					printf("\n输入有误,本次评测作废");
					colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
					Sleep(1500);
					return (MBTI);
			}
		} 
		else if(i >= 15 && i <= 21){
			switch (n) {
				case 1 :
				    out.m[4]+=1;
					break;
				case 2 :
					out.m[5]+=1;
					break;
				default :
					printf("\n输入有误,本次评测作废");
					colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
					Sleep(1500);
					return (MBTI);
			}
		} 
		else{
			switch (n) {
				case 1 :
				    out.m[6]+=1;
					break;
				case 2 :
					out.m[7]+=1;
					break;
				default :
					printf("\n输入有误,本次评测作废");
					colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(1秒后自动返回)\n");
					Sleep(1500);
					return (MBTI);
			}
		} 
	}
	if(out.m[0]>out.m[1] && out.m[2]>out.m[3] && out.m[4]>out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "ENFJ/主人公");} 
	if(out.m[0]<out.m[1] && out.m[2]<out.m[3] && out.m[4]<out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "ISTP/鉴赏家");} 
	if(out.m[0]>out.m[1] && out.m[2]>out.m[3] && out.m[4]<out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "ENTP/辩论家");} 
	if(out.m[0]>out.m[1] && out.m[2]>out.m[3] && out.m[4]>out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "ENFP/竞选者");} 
	if(out.m[0]>out.m[1] && out.m[2]>out.m[3] && out.m[4]<out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "ENTJ/指挥官");} 
	if(out.m[0]>out.m[1] && out.m[2]<out.m[3] && out.m[4]>out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "ESFJ/执政官");} 
	if(out.m[0]>out.m[1] && out.m[2]<out.m[3] && out.m[4]<out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "ESTP/企业家");} 
	if(out.m[0]>out.m[1] && out.m[2]<out.m[3] && out.m[4]>out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "ESFP/表演者");} 
	if(out.m[0]>out.m[1] && out.m[2]<out.m[3] && out.m[4]<out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "ESTJ/总经理");}
	if(out.m[0]<out.m[1] && out.m[2]<out.m[3] && out.m[4]>out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "ISFJ/守卫者");} 
	if(out.m[0]<out.m[1] && out.m[2]<out.m[3] && out.m[4]<out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "ISTJ/物流师");} 
	if(out.m[0]<out.m[1] && out.m[2]<out.m[3] && out.m[4]>out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "ISFP/探险家");} 
	if(out.m[0]<out.m[1] && out.m[2]>out.m[3] && out.m[4]>out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "INFJ/提倡者");} 
	if(out.m[0]<out.m[1] && out.m[2]>out.m[3] && out.m[4]<out.m[5] && out.m[6]>out.m[7]) {
		strcpy(out.c, "INTJ/建筑师");} 
	if(out.m[0]<out.m[1] && out.m[2]>out.m[3] && out.m[4]>out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "INFP/调停者");} 
	if(out.m[0]<out.m[1] && out.m[2]>out.m[3] && out.m[4]<out.m[5] && out.m[6]<out.m[7]) {
		strcpy(out.c, "INTP/逻辑学家");} 
	printf("\n测试完成,请返回查看结果");
	colorful_printf(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,"(按任意键返回)\n");
	getch();
    return(out);
}

