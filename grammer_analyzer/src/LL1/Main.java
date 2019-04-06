package LL1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    String Vn[]={ "E" , "E'" , "T" , "T'" , "F" };//文法的非终结符集
    String Vt[]={ "i" , "+", "*" , "(" , ")" , "$"};//文法的终结符集
    String tb[][] = new String[5][6];//定义预测分析表
    String stack[];//定义分析栈
    int count = 1;//步骤
    int ptr1 = 1;//分析栈指针
    int ptr2 = 0,ptr3 =0;//预测分析表指针
    String inputString = "";//定义输入字符串
    boolean flag;
    public void setCount(int count,int ptr1,int ptr2,int ptr3){
        this.count = count;
        this.ptr1 = ptr1;
        this.ptr2 = ptr2;
        this.ptr3 = ptr3;
        this.flag = false;
    }

    public void InitStack(){//初始化分析栈，栈内存放#和文法开始符号E
        this.stack = new String[20];
        stack[0] = "$";
        stack[1] = "E";
    }

    public void setTb() { //初始化预测分析表
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                this.tb[i][j] = null;
            }
        }
        this.tb[0][0] = "->TE'";
        this.tb[0][4] = "synch";
        this.tb[0][5] = "synch";
        this.tb[0][3] = "->TE'";
        this.tb[1][1] = "->+TE'";
        this.tb[1][4] = "->#";
        this.tb[1][5] = "->#";
        this.tb[2][0] = "->FT'";
        this.tb[2][3] = "->FT'";
        this.tb[3][1] = "->#";
        this.tb[3][2] = "->*FT'";
        this.tb[3][4] = "->#";
        this.tb[3][5] = "->#";
        this.tb[4][0] = "->i";
        this.tb[4][3] = "->(E)";
        this.tb[2][4] = "synch";
        this.tb[2][1] = "synch";
        this.tb[2][5] = "synch";
        this.tb[4][4] = "synch";
        this.tb[4][1] = "synch";
        this.tb[4][2] = "synch";
        this.tb[4][5] = "synch";
}

    public void setInputString(String input){
        this.inputString = input;
    }

    public boolean judge() {
        String inputChar = this.inputString.substring(0, 1);//当前输入字符
        boolean terminal = false;
        if (ptr1 >= 0) {//当前栈不为空
            for (int i = 0; i < 6; i++) {
                if (stack[ptr1].equals(Vt[i])) {//如果当前栈顶元素匹配到某个终结符号
                    terminal = true;
                    break;//找到就直接跳出for循环
                }
            }
        }
        if (terminal) {//当前栈顶为终结符
            if (stack[ptr1].equals(inputChar)) {//栈顶终结符与当前输入字符相同
                if (stack[ptr1].equals("$") && inputString.length() == 1) {
                    //当栈顶符号为结束标志,并且当前剩余字符串也为结束标志
                    String temp = "";
                    for (int i = 0; i <= tb.length; i++) {//拿到分析栈里的全部内容
                        if (stack[i] == null) {
                            break;
                        } else {
                            temp = temp + stack[i];
                        }
                    }
                    //输出当前分析栈情况，输入字符串，所用产生式或匹配
                    //进行输出格式控制，保证界面友好易于分析
                    System.out.print("  " + count);
                    String countToString = Integer.toString(count);
                    int farWay = 14 - countToString.length();
                    for (int k = 0; k < farWay; k++) {
                        System.out.print(" ");
                    }
                    System.out.print(temp);
                    farWay = 20 - temp.length();
                    for (int k = 0; k < farWay; k++) {
                        System.out.print(" ");
                    }
                    System.out.print(inputString);
                    farWay = 25 - inputString.length();
                    for (int k = 0; k < farWay; k++) {
                        System.out.print(" ");
                    }
                    System.out.println("接受");
                    flag = true;
                    return true;
                } else {//分析栈栈顶的终结符不是结束标志$时
                    String temp = "";
                    for (int i = 0; i <= tb.length; i++) {
                        if (stack[i] == null) {
                            break;
                        } else {
                            temp = temp + stack[i];
                        }
                    }
                    System.out.print("  " + count);
                    String countToString = Integer.toString(count);
                    int farWay = 14 - countToString.length();
                    for (int k = 0; k < farWay; k++) {
                        System.out.print(" ");
                    }
                    System.out.print(temp);
                    farWay = 20 - temp.length();
                    for (int k = 0; k < farWay; k++) {
                        System.out.print(" ");
                    }
                    System.out.print(inputString);
                    farWay = 25 - inputString.length();
                    for(int k = 0;k<farWay;k++){
                        System.out.print(" ");
                    }
                    System.out.println("\"" + inputChar + "\"" + "匹配");
                    //弹出栈顶符号，栈顶指针减1
                    stack[ptr1] = null;
                    ptr1--;
                    if (inputString.length() > 1) {//若当前输入字符串的长度大于1时，将当前输入字符从输入字符串中除去
                        inputString = inputString.substring(1, inputString.length());
                    } else {//当前输入串长度为1时
                        inputChar = inputString;
                    }
                    count++;
                    judge();
                }
            } else {//当前栈顶符号为终结符且与输入符号不匹配
                System.out.println("       分析到第" + count + "步时出错!");
                System.out.println("       错误原因：当前输入符号 " + inputChar + " 与栈顶的终结符号不匹配！");
                System.out.println("       将进行错误处理——弹出栈顶终结符号");

                flag = false;
                //错误处理：弹出栈顶终结符号
                stack[ptr1] = null;
                ptr1--;
                judge();

                return false;
            }

        } else {//若栈顶符号为非终结符时
            boolean fla = false;
            for (int i = 0; i < 6; i++) {//查询当前输入符号位于终结符集的哪个位置
                if (inputChar.equals(Vt[i])) {
                    fla = true;
                    ptr2 = i;
                    break;
                }
            }
            if (!fla) {
                System.out.println("       分析到第" + count + "步时出错!");
                System.out.println("       错误原因：当前输入符号 " + inputChar + " 不在所用文法的终结符集中!");
                System.out.println("       不进行错误处理......");
                flag = false;
                return false;
            }
            for (int i = 0; i < 5; i++) {//查询栈顶的符号位于非终结符集的位置
                if (stack[ptr1].equals(Vn[i])) {
                    ptr3 = i;
                    break;
                }
            }
            if (tb[ptr3][ptr2] != null) {
                if(!tb[ptr3][ptr2].equals("synch")) {
                    String chanshengshi = tb[ptr3][ptr2];
                    String youbu = chanshengshi.substring(2, chanshengshi.length());
                    if (youbu.equals("#")) {//如果产生式推出#时
                        String temp = "";
                        for (int i = 0; i <= tb.length; i++) {
                            if (stack[i] == null) {
                                break;
                            } else {
                                temp = temp + stack[i];
                            }
                        }
                        //输出当前分析栈情况，输出字符串，所用产生式匹配
                        System.out.print("  " + count);
                        String countToString = Integer.toString(count);
                        int farWay = 14 - countToString.length();
                        for (int k = 0; k < farWay; k++) {
                            System.out.print(" ");
                        }
                        System.out.print(temp);
                        farWay = 20 - temp.length();
                        for (int k = 0; k < farWay; k++) {
                            System.out.print(" ");
                        }
                        System.out.print(inputString);
                        farWay = 25 - inputString.length();
                        for (int k = 0; k < farWay; k++) {
                            System.out.print(" ");
                        }
                        System.out.println(stack[ptr1] + tb[ptr3][ptr2]);
                        //将栈顶元素出栈，栈顶指针减1
                        stack[ptr1] = null;
                        ptr1--;
                        count++;
                        judge();
                    } else {//产生式不推出ε时
                        int k = youbu.length();//统计产生式右部的符号个数
                        String temp = "";
                        for (int i = 0; i <= tb.length; i++) {
                            if (stack[i] == null) {
                                break;
                            } else {
                                temp = temp + stack[i];
                            }
                        }
                        //输出当前分析栈的情况，输入字符串，所用产生式或匹配
                        System.out.print("  " + count);
                        String countToString = Integer.toString(count);
                        int farWay = 14 - countToString.length();
                        for (int j = 0; j < farWay; j++) {
                            System.out.print(" ");
                        }
                        System.out.print(temp);
                        farWay = 20 - temp.length();
                        for (int j = 0; j < farWay; j++) {
                            System.out.print(" ");
                        }
                        System.out.print(inputString);
                        farWay = 25 - inputString.length();
                        for (int j = 0; j < farWay; j++) {
                            System.out.print(" ");
                        }
                        System.out.println(stack[ptr1] + tb[ptr3][ptr2]);
                        for (int i = 1; i <= k; i++) {//将产生式右部的k个符号入栈
                            String ch = youbu.substring(youbu.length() - 1, youbu.length());
                            youbu = youbu.substring(0, youbu.length() - 1);
                            if (ch.equals("'")) {
                                ch = youbu.substring(youbu.length() - 1, youbu.length()) + ch;
                                i++;//取两次符号，必须自加1
                                youbu = youbu.substring(0, youbu.length() - 1);
                            }
                            stack[ptr1] = ch;//栈顶元素先弹出，再入栈，相当于被替代
                            if (i < k)
                                ptr1++;
                        }
                        count++;
                        judge();
                    }
                }else{//分析表入口为synch
                    System.out.println("      分析到第" + count + "步时出错!");
                    System.out.println("      错误原因：当前栈顶的非终结符 " + stack[ptr1] + " 在分析表的入口为synch！");
                    System.out.println("       将进行错误处理——弹出当前栈顶符号");
                    stack[ptr1]=null;
                    ptr1--;
                    judge();
                    flag = false;
                    return false;

                }
            } else {//分析表入口为空
                System.out.println("       分析到第" + count + "步时出错!");
                System.out.println("       错误原因：当前栈顶的非终结符 " + stack[ptr1] + " 在分析表的入口为空!");
                System.out.println("       将进行错误处理——跳过当前输入符号");
                inputString = inputString.substring(1,inputString.length());
                judge();
                flag = false;
                return false;
            }
        }
        return flag;
    }

    public static void main(String[] args){
        Main l = new Main();
        l.setTb();
        String input = "";
        boolean flag = true;
        while(flag) {//flag为false时退出循环，即退出程序
            try {
                InputStreamReader isr = new InputStreamReader(System.in);
                BufferedReader br = new BufferedReader(isr);
                System.out.println();
                System.out.println("请输入需要判断的字符串(若输入exit则退出本次操作)：");
                input = br.readLine();
            } catch (Exception e) {
                e.printStackTrace();
            }
            if(input.equals("exit")){
                flag = false;
            }else{
                l.setInputString(input);
                l.setCount(1,1,0,0);
                l.InitStack();
                System.out.println();
                System.out.println("分析过程");
                System.out.println("----------------------------------------------------------------------");
                System.out.println("   步骤  |       分析栈      |     剩余输入串     |      所用产生式    ");
                System.out.println("----------------------------------------------------------------------");
                boolean b = l.judge();
                System.out.println("----------------------------------------------------------------------");
                if(b){
                    System.out.println("您输入的字符串 "+input+" 是符合该文法的一个合法句子");
                }else{
                    System.out.println("您输入的字符串 "+input+" 是非法的句子！");
                }
            }
        }
    }
}

