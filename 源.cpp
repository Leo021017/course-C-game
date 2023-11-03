#include<stdio.h>
#include<stdlib.h>															
#include<windows.h>													
#include<conio.h>
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#include<time.h>

//引用Windows Multimedia API
#pragma comment(lib,"Winmm.lib")            //能够播放音乐

#define zombie_num 10           //用宏来设置僵尸数目全局变量(初始化为10)，便于定义僵尸数组

const int game_width = 1200;            //定义游戏界面的宽
const int game_high = 720;          //定义游戏界面的高

IMAGE background_start;         //定义开始界面背景
IMAGE background_playing;           //定义游戏界面背景             
IMAGE bean_card;            //定义豌豆卡牌
IMAGE bean_card_s;
IMAGE sunflower_card;          //定义向日葵卡牌
IMAGE sunflower_card_s;
IMAGE nut_card;         //定义坚果卡牌
IMAGE nut_card_s;
IMAGE bean_0;           //定义豌豆射手
IMAGE bean_1;
IMAGE bean_2;
IMAGE bean_0_s;
IMAGE bean_1_s;
IMAGE bean_2_s;
IMAGE sunflower_0;          //定义向日葵
IMAGE sunflower_1;
IMAGE sunflower_2;
IMAGE sunflower_0_s;
IMAGE sunflower_1_s;
IMAGE sunflower_2_s;
IMAGE nut;          //定义坚果
IMAGE nut_s;
IMAGE seedbank;         //定义种子银行
IMAGE dog;          //定义狗头子弹
IMAGE dog_s;
IMAGE sun_0;            //定义太阳
IMAGE sun_1;          
IMAGE sun_2;          
IMAGE sun_3;
IMAGE sun_4;
IMAGE sun_5;
IMAGE sun_0_s;           
IMAGE sun_1_s;
IMAGE sun_2_s;
IMAGE sun_3_s;
IMAGE sun_4_s;
IMAGE sun_5_s;
IMAGE game_gg;          //定义游戏失败的界面
IMAGE victory1;          //定义游戏胜利的提醒图片
IMAGE victory2;
IMAGE zombie_walking0;          //定义僵尸
IMAGE zombie_walking1;
IMAGE zombie_walking2;
IMAGE zombie_walking3;
IMAGE zombie_walking4;
IMAGE zombie_walking5;
IMAGE zombie_walking6;
IMAGE zombie_walking7;
IMAGE zombie_walking8;
IMAGE zombie_walking9;
IMAGE zombie_walking10;
IMAGE zombie_walking11;
IMAGE zombie_walking0_s;
IMAGE zombie_walking1_s;
IMAGE zombie_walking2_s;
IMAGE zombie_walking3_s;
IMAGE zombie_walking4_s;
IMAGE zombie_walking5_s;
IMAGE zombie_walking6_s;
IMAGE zombie_walking7_s;
IMAGE zombie_walking8_s;
IMAGE zombie_walking9_s;
IMAGE zombie_walking10_s;
IMAGE zombie_walking11_s;
IMAGE shovel;           //定义铲子
IMAGE shovel_s;
IMAGE scdx;         //定义川大校徽
IMAGE dave;
IMAGE dave_s;
IMAGE car;
IMAGE car_s;

int gamestatus = 0;         //游戏的状态（0是开始菜单、3是暂停菜单、4是胜利结束菜单、5是失败结束菜单）

int show_bean;          //是否显示豌豆
int show_sunflower;         //是否显示向日葵
int show_nut;           //是否显示坚果
int bean_x;         //定义豌豆的坐标
int bean_y;
int sunflower_x;            //定义向日葵的坐标
int sunflower_y;
int nut_x;          //定义坚果坐标
int nut_y;
int is_planted;         //植物是否种植过
int map[10][5];         //0表示什么都没种，1表示种了豌豆，2表示种了向日葵，3表示种了坚果
int is_bean_move = 0;           //豌豆是否能够移动
int is_sunflower_move = 0;          //向日葵是否能够移动
int is_nut_move;            //坚果是否能够移动
int i, j, z, t, c;         //for循环使用(i和j种植物用，i表示9列，j表示5行，z判断僵尸和子弹的时候用，t减慢移动速度时用）
int size_width;         //定义每一个草地格子的高
int size_high;         //定义每一个草地格子的宽
int Px;         //定义草地横坐标偏移量
int Py;         //定义草地纵坐标偏移量
int zombie_x[zombie_num] = { 1300,1300,1300,1400,1500,1500,1700,1800,1900,1900 };
int zombie_y[zombie_num];
int zombie_v[zombie_num];       //定义僵尸的速度(数组表示每一个僵尸的初速度都定义下来)
int is_zombie[zombie_num];            //定义僵尸是否出现（或是否活着）
int dead_zombie;
int hit[zombie_num];          //定义僵尸的受击打数   
int is_shot[9][5];          //定义子弹是否显示
int shot_x[9][5];           //定义子弹的坐标
int shot_y[9][5];
int shot_v[9][5];           //定义子弹发射的速度
int sun_x;          //定义太阳的坐标
int sun_y;
int sun_num;            //定义获取到的阳光的数量
int sun_v;          //定义太阳下落的速度
int planted_sunflower_num;          //定义已种植向日葵的数目
int is_shovel;          //定义是否显示铲子
int is_shovel_move;         //定义铲子是否能跟随鼠标移动
int shovel_x;           //定义铲子的坐标
int shovel_y;
int is_choose;          //定义是否选择过卡牌
int car_x[5];           //定义小车的坐标
int car_y[5];
int car_v[5];           //定义小车的速度
int is_car_move[5];         //定义小车是否开始移动

void start_menu();          //开始菜单函数
void pause_menu();          //暂停菜单函数
void startup();             //参数初始化函数
void show();            //显示画面函数
void updateWithoutInput();          //与用户输入无关的更新
void updateWithInput();         //与用户输入有关的更新
void gameover();            //游戏结束
void Game_gg();         //游戏失败
void Game_nice();           //游戏胜利

int main()
{
    startup();
    while (1)
    {
        show();
        updateWithoutInput();
        updateWithInput();
    }
    gameover();
    return 0;
}

void start_menu()
{
    putimage(0, 0, &background_start);          //加载开始界面背景图片

    const int button_width = 150;           //定义按钮的宽
    const int button_high = 50;         //定义按钮的高
    const int button_textsize = 30;         //定义按钮内文本的大小
    const int button_intervel = 30;         //定义两个按钮的间距
    char ch_start[6] = "START"; char ch_quit[5] = "QUIT";         //定义按钮文字的文本

    int button_start_x = (game_width - button_width) / 2;           //求出START按钮的坐标
    int button_start_y = (game_high - 2 * button_high - button_intervel) / 2;
    int button_quit_x = button_start_x;         //求出QUIT按钮的坐标
    int button_quit_y = button_start_y + button_intervel + button_high;
    int text_start_x = button_start_x + (button_width - textwidth(ch_start)) / 2;           //求出START文本的坐标
    int text_start_y = button_start_y + (button_high - textheight(ch_start)) / 2;
    int text_quit_x = button_quit_x + (button_width - textwidth(ch_quit)) / 2;          //求出QUIT文本的坐标
    int text_quit_y = button_quit_y + (button_high - textheight(ch_quit)) / 2;

    setbkmode(TRANSPARENT);         //设置字体背景透明、字体格式
    settextstyle(button_textsize, 0, "黑体");

    //画出按钮和按钮上的文字（15表示圆角矩形的曲度）
    setfillcolor(RED);          //设置圆角矩形的填充色
    fillroundrect(button_start_x, button_start_y, button_start_x + button_width, button_start_y + button_high, 15, 15);
    fillroundrect(button_quit_x, button_quit_y, button_quit_x + button_width, button_quit_y + button_high, 15, 15);
    outtextxy(text_start_x, text_start_y, ch_start);
    outtextxy(text_quit_x, text_quit_y, ch_quit);

    setbkmode(TRANSPARENT);         //设置字体背景透明、字体格式
    settextstyle(button_textsize, 0, "黑体");
    setcolor(WHITE);
    char tips[50] = "游戏中按Esc键可以暂停游戏";
    outtextxy((game_width - textwidth(tips)) / 2, 550, tips);

    FlushBatchDraw();           //注意和EndBatchDraw()的区别

    ExMessage mouse_start;          //定义一个鼠标消息
    if (peekmessage(&mouse_start, EM_MOUSE))            //如果鼠标有消息
    {
        switch (mouse_start.message)
        {
        case WM_LBUTTONDOWN:            //如果是左键
            if (mouse_start.x >= button_start_x && mouse_start.x <= button_start_x + button_width &&
                mouse_start.y >= button_start_y && mouse_start.y <= button_start_y + button_high)
            {
                mciSendString("close button", NULL, 0, NULL);
                mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
                mciSendString("play button", NULL, 0, NULL);

                mciSendString("close start", NULL, 0, NULL);
                mciSendString("open ./zombie_coming.mp3 alias start", NULL, 0, NULL);
                mciSendString("play start", NULL, 0, NULL);

                gamestatus = 1;         //调整游戏状态为正式开始游戏（START键）
            }
            else if (mouse_start.x >= button_quit_x && mouse_start.x <= button_quit_x + button_width &&
                mouse_start.y >= button_quit_y && mouse_start.y <= button_quit_y + button_high)
            {
                mciSendString("close button", NULL, 0, NULL);
                mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
                mciSendString("play button", NULL, 0, NULL);

                closegraph();           //关掉游戏窗口（QUIT键）
            }
            break;
        }
    }
}

void show()
{
    while (gamestatus == 3)         //满足条件进入暂停画面函数
        pause_menu();

    while (gamestatus == 5)         //满足条件进入游戏失败界面
        Game_gg();

    while (gamestatus == 4)         //满足条件进入游戏胜利界面
        Game_nice();

    mciSendString("open ./bk_music.mp3 alias msc", NULL, 0, NULL);          //播放背景音乐
    mciSendString("play msc repeat ", NULL, 0, NULL);

    putimage(0, 0, &background_playing);            //加载游戏界面背景

    int timer = (double)clock() / CLOCKS_PER_SEC * 1000;           //获取程序运行的时间（毫秒为单位）
    int maeda = timer / 200;            //得到一个合理的时间间隔

    if (show_bean == 1)         //如果鼠标选到了豌豆
    {
        int frame_bean = 3;         //定义豌豆射手图片的帧数，以相同的时间间隔循环播放
        if (maeda % frame_bean == 0)
        {
            putimage(bean_x, bean_y, &bean_0_s, NOTSRCERASE);
            putimage(bean_x, bean_y, &bean_0, SRCINVERT);
        }
        if (maeda % frame_bean == 1)
        {
            putimage(bean_x, bean_y, &bean_1_s, NOTSRCERASE);
            putimage(bean_x, bean_y, &bean_1, SRCINVERT);
        }
        if (maeda % frame_bean == 2)
        {
            putimage(bean_x, bean_y, &bean_2_s, NOTSRCERASE); 
            putimage(bean_x, bean_y, &bean_2, SRCINVERT);
        }
    }

    if (show_sunflower == 1)            //如果鼠标选到了向日葵
    {
        int frame_sunflower = 3;            //定义向日葵图片的帧数，以相同的时间间隔循环播放
        if (maeda % frame_sunflower == 0)
        {
            putimage(sunflower_x, sunflower_y, &sunflower_0_s, NOTSRCERASE);
            putimage(sunflower_x, sunflower_y, &sunflower_0, SRCINVERT);
        }
        if (maeda % frame_sunflower == 1)
        {
            putimage(sunflower_x, sunflower_y, &sunflower_1_s, NOTSRCERASE);
            putimage(sunflower_x, sunflower_y, &sunflower_1,SRCINVERT);
        }
        if (maeda % frame_sunflower == 2)
        {
            putimage(sunflower_x, sunflower_y, &sunflower_2_s, NOTSRCERASE);
            putimage(sunflower_x, sunflower_y, &sunflower_2, SRCINVERT);
        }
    }

    if (show_nut == 1)          //如果鼠标选到了坚果 
    {
        putimage(nut_x, nut_y, &nut_s, NOTSRCERASE);
        putimage(nut_x, nut_y, &nut, SRCINVERT);
    }

    if (is_shovel == 1)         //如果鼠标选到了铲子
    {
        putimage(shovel_x, shovel_y, &shovel_s, NOTSRCERASE);
        putimage(shovel_x, shovel_y, &shovel, SRCINVERT);
    }

    for (i = 0; i < 9; i++)         //for循环遍历草地上的所有方块
    {
        for (j = 0; j < 5; j++)
        {
            if (map[i][j] == 1)         //如果这个格子种了豌豆，显示豌豆
            {
                int frame_bean = 3;
                if (maeda % frame_bean == 0)
                {
                    putimage(Px + size_width * i, Py + size_high * j, &bean_0_s, NOTSRCERASE);
                    putimage(Px + size_width * i, Py + size_high * j, &bean_0, SRCINVERT);
                }
                if (maeda % frame_bean == 1)
                {
                    putimage(Px + size_width * i, Py + size_high * j, &bean_1_s,NOTSRCERASE);
                    putimage(Px + size_width * i, Py + size_high * j, &bean_1, SRCINVERT);
                }
                if (maeda % frame_bean == 2)
                {
                    putimage(Px + size_width * i, Py + size_high * j, &bean_2_s, NOTSRCERASE);
                    putimage(Px + size_width * i, Py + size_high * j, &bean_2, SRCINVERT);
                }
            }
        }
    }

    for (i = 0; i < 9; i++)         //for循环遍历草地上的所有方块
    {
        for (j = 0; j < 5; j++)
        {
            if (map[i][j] == 2)         //如果这个地方种了向日葵
            {
                int frame_sunflower = 3;
                if (maeda % frame_sunflower == 0)
                {
                    putimage(Px + size_width * i, Py + size_high * j, &sunflower_0_s, NOTSRCERASE);
                    putimage(Px + size_width * i, Py + size_high * j, &sunflower_0, SRCINVERT);
                }
                if (maeda % frame_sunflower == 1)
                {
                    putimage(Px + size_width * i, Py + size_high * j, &sunflower_1_s, NOTSRCERASE);
                    putimage(Px + size_width * i, Py + size_high * j, &sunflower_1, SRCINVERT);
                }
                if (maeda % frame_sunflower == 2)
                {
                    putimage(Px + size_width * i, Py + size_high * j, &sunflower_2_s, NOTSRCERASE);
                    putimage(Px + size_width * i, Py + size_high * j, &sunflower_2, SRCINVERT);
                }
            }
        }
    }

    for (i = 0; i < 9; i++)         //for循环遍历草地上的所有方块
    {
        for (j = 0; j < 5; j++)
        {
            if (map[i][j] == 3)         //如果这个地方种了坚果
            {
                putimage(Px + size_width * i, Py + size_high * j, &nut_s, NOTSRCERASE);
                putimage(Px + size_width * i, Py + size_high * j, &nut, SRCINVERT);
            }
        }
    }

    for (z = 0; z < zombie_num; z++)            //对每一个僵尸进行遍历，判断是否还可以显示僵尸（僵尸是否还活着）
    {
        if (is_zombie[z] == 1)
        {            
            int frame_zombie = 12;
            if (maeda % frame_zombie == 0)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking0_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking0, SRCINVERT);
            }
            if (maeda % frame_zombie == 1)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking1_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking1, SRCINVERT);
            }
            if (maeda % frame_zombie == 2)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking2_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking2, SRCINVERT);
            }
            if (maeda % frame_zombie == 3)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking3_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking3, SRCINVERT);
            }
            if (maeda % frame_zombie == 4)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking4_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking4, SRCINVERT);
            }
            if (maeda % frame_zombie == 5)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking5_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking5, SRCINVERT);
            }
            if (maeda % frame_zombie == 6)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking6_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking6, SRCINVERT);
            }
            if (maeda % frame_zombie == 7)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking7_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking7, SRCINVERT);
            }
            if (maeda % frame_zombie == 8)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking8_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking8, SRCINVERT);
            }
            if (maeda % frame_zombie == 9)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking9_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking9, SRCINVERT);
            }
            if (maeda % frame_zombie == 10)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking10_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking10, SRCINVERT);
            }
            if (maeda % frame_zombie == 11)
            {
                putimage(zombie_x[z], zombie_y[z], &zombie_walking11_s, NOTSRCERASE);
                putimage(zombie_x[z], zombie_y[z], &zombie_walking11, SRCINVERT);
            }
        }
    }

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (is_shot[i][j] == 1 && map[i][j] == 1)           //豌豆射手发射子弹
            {   
                putimage(shot_x[i][j], shot_y[i][j], &dog_s, NOTSRCERASE);
                putimage(shot_x[i][j], shot_y[i][j], &dog, SRCINVERT);
            }
        }
    }

    putimage(0, 0, &seedbank);          //显示种子银行

    if (sun_num >= 100)         //阳光数够100可以种豌豆，卡牌亮，否则不亮
    {
        putimage(105, 5, &bean_card);        
    }
    else
    {
        putimage(105, 5, &bean_card_s);
    }
    if (sun_num >= 50)          //阳光数够50可以种向日葵，卡牌亮，否则不亮
    {
        putimage(192, 5, &sunflower_card);           
    }
    else
    {
        putimage(192, 5, &sunflower_card_s);
    }
    if (sun_num >= 500)         //阳光数够100可以种坚果，卡牌亮，否则不亮
    {
        putimage(279, 5, &nut_card);
    }
    else
    {
        putimage(279, 5, &nut_card_s);
    }

    for (c = 0; c < 5; c++)         //显示小车
    {
        putimage(car_x[c], car_y[c], &car_s, NOTSRCERASE);
        putimage(car_x[c], car_y[c], &car, SRCINVERT);
    }

    putimage(366, 5, &shovel_s, NOTSRCERASE);           //显示铲子
    putimage(366, 5, &shovel, SRCINVERT);

    int maeda_sun = timer / 200;            //显示下落的太阳
    int frame_sun = 6;
    if (maeda_sun % frame_sun == 0)
    {
        putimage(sun_x, sun_y, &sun_0_s, NOTSRCERASE);
        putimage(sun_x, sun_y, &sun_0, SRCINVERT);
    }
    if (maeda_sun % frame_sun == 1)
    {
        putimage(sun_x, sun_y, &sun_1_s, NOTSRCERASE);
        putimage(sun_x, sun_y, &sun_1, SRCINVERT);
    }
    if (maeda_sun % frame_sun == 2)
    {
        putimage(sun_x, sun_y, &sun_2_s, NOTSRCERASE);
        putimage(sun_x, sun_y, &sun_2, SRCINVERT);
    }
    if (maeda_sun % frame_sun == 3)
    {
        putimage(sun_x, sun_y, &sun_3_s, NOTSRCERASE);
        putimage(sun_x, sun_y, &sun_3, SRCINVERT);
    }
    if (maeda_sun % frame_sun == 4)
    {
        putimage(sun_x, sun_y, &sun_4_s, NOTSRCERASE);
        putimage(sun_x, sun_y, &sun_4, SRCINVERT);
    }
    if (maeda_sun % frame_sun == 5)
    {
        putimage(sun_x, sun_y, &sun_5_s, NOTSRCERASE);
        putimage(sun_x, sun_y, &sun_5, SRCINVERT);
    }

    setbkmode(TRANSPARENT);         //显示当前阳光数
    setcolor(BLACK);
    settextstyle(30, 0, "黑体");
    char s1[50];
    sprintf_s(s1, "%d\n", sun_num);
    outtextxy(26, 90, s1);

    setbkmode(TRANSPARENT);         //显示开始时间
    setcolor(BLACK);
    settextstyle(30, 0, "黑体");
    char s2[50];
    sprintf_s(s2, "已经开始%d秒了\n", (int)clock() / CLOCKS_PER_SEC);
    outtextxy(0, 250, s2);

    putimage(1120, 0, &scdx);           //显示校徽

    FlushBatchDraw();           //进行一次绘图
}

void startup()
{
    initgraph(game_width, game_high);           //设置并打开图形窗口

    bean_x = 105;         //初始化豌豆的坐标
    bean_y = 5;
    sunflower_x = 192;            //初始化向日葵的坐标
    sunflower_y = 5;
    Px = 375;           //初始化草地偏移量
    Py = 140;
    show_bean = 0;          //初始化不显示植物
    show_sunflower = 0;
    show_nut = 0;
    is_bean_move = 0;           //初始化植物不能移动
    is_sunflower_move = 0;         
    is_nut_move = 0;         
    is_shovel = 0;          //初始化铲子不显示
    is_shovel_move = 0;         //初始化铲子不能移动
    is_planted = 0;         //初始植物没有完成种植
    is_choose = 0;          //初始化没有选择卡牌
    size_width = 82;           //初始化草地方块的大小
    size_high = 103;
    sun_x = rand() % (game_width - 375) + 375;          //初始化太阳的随机横坐标
    sun_y = -400;           //初始化太阳的随机纵坐标
    sun_num = 300;          //初始化太阳数
    sun_v = 10;          //初始化太阳下落的速度

    for (z = 0; z < zombie_num; z++)            //将每一个僵尸的状态都初始化
    {
        zombie_y[z] = (rand() % 5) * size_high + Py;
        zombie_v[z] = -1;           //初始化僵尸速度
        is_zombie[z] = 1;           //初始化僵尸都先出现
        hit[z] = 0;         //初始化僵尸的受击打数为0
    }

    for (i = 0; i < 9; i++)         //初始化所有格子对应的狗头子弹的参数
    {
        for (j = 0; j < 5; j++)
        {
            is_shot[i][j] = 0;
            shot_v[i][j] = 30;
            shot_x[i][j] = 0;
            shot_y[i][j] = 0;
        }
    }

    for (c = 0; c < 5; c++)
    {
        car_v[c] = 15;
        car_y[c] = Py + c * size_high;
        car_x[c] = Px - 110;
        is_car_move[c] = 0;
    }

    loadimage(&background_start, "./开始界面.jpg");         //准备加载图片
    loadimage(&background_playing, "./背景图片.jpg");
    loadimage(&bean_card, "./豌豆卡牌.png");
    loadimage(&bean_card_s, "./豌豆卡牌暗.png");
    loadimage(&sunflower_card, "./向日葵卡牌.png");
    loadimage(&sunflower_card_s, "./向日葵卡牌暗.png");
    loadimage(&nut_card, "./坚果卡牌.jpg");
    loadimage(&nut_card_s, "./坚果卡牌暗.jpg");
    loadimage(&bean_0, "./豌豆0.png");
    loadimage(&bean_1, "./豌豆1.png");
    loadimage(&bean_2, "./豌豆2.png");
    loadimage(&bean_0_s, "./豌豆0_s.png");
    loadimage(&bean_1_s, "./豌豆1_s.png");
    loadimage(&bean_2_s, "./豌豆2_s.png");
    loadimage(&sunflower_0, "./向日葵0.png");
    loadimage(&sunflower_1, "./向日葵1.png");
    loadimage(&sunflower_2, "./向日葵2.png");
    loadimage(&sunflower_0_s, "./向日葵0_s.png");
    loadimage(&sunflower_1_s, "./向日葵1_s.png");
    loadimage(&sunflower_2_s, "./向日葵2_s.png");
    loadimage(&nut_s, "./坚果_s.jpg");
    loadimage(&nut, "./坚果.jpg");
    loadimage(&seedbank, "./种子银行.png");
    loadimage(&sun_0, "./太阳0.png");
    loadimage(&sun_1, "./太阳1.png");
    loadimage(&sun_2, "./太阳2.png");
    loadimage(&sun_3, "./太阳3.png");
    loadimage(&sun_4, "./太阳4.png");
    loadimage(&sun_5, "./太阳5.png");
    loadimage(&sun_0_s, "./太阳0_s.png");
    loadimage(&sun_1_s, "./太阳1_s.png");
    loadimage(&sun_2_s, "./太阳2_s.png");
    loadimage(&sun_3_s, "./太阳3_s.png");
    loadimage(&sun_4_s, "./太阳4_s.png");
    loadimage(&sun_5_s, "./太阳5_s.png");
    loadimage(&game_gg, "./失败.png");
    loadimage(&dog, "./狗头.png");
    loadimage(&dog_s, "./狗头_s.png");
    loadimage(&victory1, "./胜利1.png");
    loadimage(&victory2, "./胜利2.png");
    loadimage(&zombie_walking0, "./僵尸行走0.jpg");
    loadimage(&zombie_walking1, "./僵尸行走1.jpg");
    loadimage(&zombie_walking2, "./僵尸行走2.jpg");
    loadimage(&zombie_walking3, "./僵尸行走3.jpg");
    loadimage(&zombie_walking4, "./僵尸行走4.jpg");
    loadimage(&zombie_walking5, "./僵尸行走5.jpg");
    loadimage(&zombie_walking6, "./僵尸行走6.jpg");
    loadimage(&zombie_walking7, "./僵尸行走7.jpg");
    loadimage(&zombie_walking8, "./僵尸行走8.jpg");
    loadimage(&zombie_walking9, "./僵尸行走9.jpg");
    loadimage(&zombie_walking10, "./僵尸行走10.jpg");
    loadimage(&zombie_walking11, "./僵尸行走11.jpg");
    loadimage(&zombie_walking0_s, "./僵尸行走0_s.jpg");
    loadimage(&zombie_walking1_s, "./僵尸行走1_s.jpg");
    loadimage(&zombie_walking2_s, "./僵尸行走2_s.jpg");
    loadimage(&zombie_walking3_s, "./僵尸行走3_s.jpg");
    loadimage(&zombie_walking4_s, "./僵尸行走4_s.jpg");
    loadimage(&zombie_walking5_s, "./僵尸行走5_s.jpg");
    loadimage(&zombie_walking6_s, "./僵尸行走6_s.jpg");
    loadimage(&zombie_walking7_s, "./僵尸行走7_s.jpg");
    loadimage(&zombie_walking8_s, "./僵尸行走8_s.jpg");
    loadimage(&zombie_walking9_s, "./僵尸行走9_s.jpg");
    loadimage(&zombie_walking10_s, "./僵尸行走10_s.jpg");
    loadimage(&zombie_walking11_s, "./僵尸行走11_s.jpg");
    loadimage(&shovel, "./铲子.png");
    loadimage(&shovel_s, "./铲子_s.png");
    loadimage(&scdx, "./校徽.jpg");
    loadimage(&dave, "./戴夫.png");
    loadimage(&dave_s, "./戴夫_s.png");
    loadimage(&car, "./小车.png");
    loadimage(&car_s, "./小车_s.png");

    BeginBatchDraw();           //开始绘图

    while (gamestatus == 0)            //满足条件进入开始菜单界面（游戏的第一个界面）
    {
        start_menu();
    }
}

void updateWithoutInput()
{
    for (z = 0; z < zombie_num; z++)            //遍历所有僵尸，使所有僵尸移动
    {
        zombie_x[z] = zombie_x[z] + zombie_v[z];
        Sleep(5);           //让僵尸缓慢移动
    }

    for (i = 0; i < 9; i++)         //遍历所有草地方块
    {
        for (j = 0; j < 5; j++)
        {
            for (z = 0; z < zombie_num; z++)            //对每一个僵尸都循环一次
            {
                if (map[i][j] == 1 && zombie_x[z] <= game_width && zombie_y[z] >= (Py + size_high * j) &&
                    zombie_y[z] < (Py + size_high * (j + 1)))           //如果僵尸与豌豆出现在了一行且僵尸走进了屏幕
                {
                    if (shot_x[i][j] < Px + size_width * i)         //这一段子弹不显示
                    {
                        is_shot[i][j] = 0;
                        shot_x[i][j] = shot_x[i][j] + shot_v[i][j];
                        shot_y[i][j] = Py + size_high * j;
                    }

                    if (shot_x[i][j] >= Px + size_width * i && shot_x[i][j] <= (zombie_x[z] + 15))          //子弹走入了植物和僵尸之间，开始显示
                    {
                        is_shot[i][j] = 1;
                        shot_x[i][j] = shot_x[i][j] + shot_v[i][j];
                        shot_y[i][j] = Py + size_high * j;
                    }  

                    if (shot_x[i][j] >= (zombie_x[z] + 15) && shot_x[i][j] < (game_width - 150))            //子弹打中了僵尸，子弹消失
                    {
                        is_shot[i][j] = 0;
                        shot_x[i][j] = shot_x[i][j] + shot_v[i][j];
                        shot_y[i][j] = Py + size_high * j;
                        shot_v[i][j] = 100;
                    }

                    if (shot_x[i][j] >= (game_width - 150))         //子弹开始掉头，依旧不显示
                    {
                        mciSendString("close hit", NULL, 0, NULL);          //播放打中僵尸的音效
                        mciSendString("open ./hit.mp3 alias hit", NULL, 0, NULL);
                        mciSendString("play hit", NULL, 0, NULL);
                        is_shot[i][j] = 0;
                        shot_x[i][j] = 0;
                        shot_y[i][j] = Py + size_high * j;
                        shot_v[i][j] = 30;
                        hit[z]++;           //僵尸扣血
                    }

                    if (hit[z] == 7)            //如果僵尸没血了，子弹和僵尸都消失
                    {
                        mciSendString("close dd", NULL, 0, NULL);
                        mciSendString("open ./death.mp3 alias dd", NULL, 0, NULL);
                        mciSendString("play dd", NULL, 0, NULL);
                        is_zombie[z] = 0;
                        zombie_v[z] = 0;
                        zombie_x[z] = 1500;
                        zombie_y[z] = 1500;
                        is_shot[i][j] = 0;
                        shot_v[i][j] = 20;
                        shot_x[i][j] = 0;
                        shot_y[i][j] = 0;
                    }
                }

                if (map[i][j] == 3 && zombie_x[z] <= game_width && zombie_x[z] <= (Px+size_width*i+60 - 10) 
                    && Py+size_high*j == zombie_y[z])           //如果僵尸走到了坚果面前
                {
                    mciSendString("close bomb", NULL, 0, NULL);
                    mciSendString("open ./bomb.mp3 alias bomb", NULL, 0, NULL);
                    mciSendString("play bomb", NULL, 0, NULL);

                    mciSendString("close dd", NULL, 0, NULL);
                    mciSendString("open ./death.mp3 alias dd", NULL, 0, NULL);
                    mciSendString("play dd", NULL, 0, NULL);
                    is_zombie[z] = 0;
                    zombie_v[z] = 0;
                    zombie_x[z] = 1500;
                    zombie_y[z] = 1500;
                    map[i][j] = 0;
                }

                if ((map[i][j] != 0) && ((zombie_x[z] - Px - size_width * i) == 35) && zombie_y[z] >= (Py + size_high * j) &&
                    zombie_y[z] < (Py + size_high * (j + 1)) && zombie_x[z] <= game_width)          //僵尸开始吃植物
                {
                    mciSendString("close eat", NULL, 0, NULL);
                    mciSendString("open ./eating_plant.mp3 alias eat", NULL, 0, NULL);
                    mciSendString("play eat", NULL, 0, NULL);
                }
                if ((map[i][j] != 0) && ((zombie_x[z] - Px - size_width * i) >= 25) && ((zombie_x[z] - Px - size_width * i) < 35)
                    && zombie_y[z] >= (Py + size_high * j) &&
                    zombie_y[z] < (Py + size_high * (j + 1)) && zombie_x[z] <= game_width)
                {
                    for (t = 1; t < 1000000000; t++);           //僵尸减速
                }
                if ((map[i][j] != 0) && ((zombie_x[z] - Px - size_width * i) == 15) && zombie_y[z] >= (Py + size_high * j) &&
                    zombie_y[z] < (Py + size_high * (j + 1)) && zombie_x[z] <= game_width)          //吃完植物，僵尸恢复速度
                {
                    map[i][j] = 0;
                    is_shot[i][j] = 0;
                    shot_v[i][j] = 20;
                    shot_x[i][j] = 0;
                    shot_y[i][j] = 0;
                }
            }
        }
    }

    for (z = 0; z < zombie_num; z++)
    {
        for (c = 0; c < 5; c++)
        {
            if (zombie_x[z] <= (car_x[c] + 110) && car_y[c] == zombie_y[z]
                && zombie_x[z] <= game_width)
            {
                mciSendString("close dd", NULL, 0, NULL);
                mciSendString("open ./death.mp3 alias dd", NULL, 0, NULL);
                mciSendString("play dd", NULL, 0, NULL);
                is_car_move[c] = 1;
                is_zombie[z] = 0;
                zombie_v[z] = 0;
                zombie_x[z] = 1500;
                zombie_y[z] = 1500;
            }
            if (is_car_move[c] == 1)
            {
                car_x[c] = car_x[c] + car_v[c];
            }
        }
    }

    for (z = 0; z < zombie_num; z++)            //如果有任何一个僵尸到家里，游戏结束（失败）
    {
        if (zombie_x[z] <= 250)
        {
            mciSendString("close cry", NULL, 0, NULL);
            mciSendString("open ./cry.mp3 alias cry", NULL, 0, NULL);
            mciSendString("play cry", NULL, 0, NULL);

            mciSendString("close msc", NULL, 0, NULL);
            mciSendString("close gg", NULL, 0, NULL);
            mciSendString("open ./gg.mp3 alias gg", NULL, 0, NULL);
            mciSendString("play gg", NULL, 0, NULL);

            gamestatus = 5;         //进入失败游戏界面
        } 
    }

    if (is_zombie[0] == is_zombie[1] && is_zombie[0] == is_zombie[2] && is_zombie[0] == is_zombie[3] && is_zombie[0]
        == is_zombie[4] && is_zombie[0] == is_zombie[5] && is_zombie[0] == is_zombie[6] && is_zombie[0] == is_zombie[7]
        && is_zombie[0] == is_zombie[8] && is_zombie[0] == is_zombie[9] && is_zombie[0] == 0)           //连等的特殊用法
    {           //僵尸全部被打死，游戏胜利
        mciSendString("close msc", NULL, 0, NULL);
        mciSendString("close victory", NULL, 0, NULL);
        mciSendString("open ./victory.mp3 alias victory", NULL, 0, NULL);
        mciSendString("play victory", NULL, 0, NULL);

        gamestatus = 4;         //进入游戏胜利界面
    }

    planted_sunflower_num = 0;          //计算出当前状态下已种植的向日葵的数量
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (map[i][j] == 2)
            {
                planted_sunflower_num++;
            }
        }
    }

    double timer1 = (double)clock() / CLOCKS_PER_SEC;
    double t = timer1 * 10;
    int timer2 = t / 10;
    if (timer2 % 5 == 0 && (timer1 - timer2) < 0.076)
    {
        mciSendString("close a", NULL, 0, NULL);
        mciSendString("open ./sunshine.mp3 alias a", NULL, 0, NULL);
        mciSendString("play a", NULL, 0, NULL);

        sun_num = sun_num + 10 * planted_sunflower_num;         //向日葵每5秒增加一定量的阳光数
    }

    sun_y = sun_y + sun_v;          //使太阳不断下落

    if (sun_y > 720)            //如果太阳掉出屏幕，重新初始化太阳坐标
    {
        sun_x = rand() % (game_width - 375) + 375;
        sun_y = -400;
    }
}

void updateWithInput()
{
    MOUSEMSG mouse_plant;          //定义一个鼠标消息
    while (MouseHit())          //当获取到一个鼠标消息时
    {
        mouse_plant = GetMouseMsg();

        //选择卡片
        if (is_planted == 0)            //如果还没有开始种植植物的过程，进行点击卡片的操作
        {

            if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= 105 && mouse_plant.x <= 180 &&
                mouse_plant.y >= 5 && mouse_plant.y <= 120 && sun_num >= 100 
                && is_choose == 0)            //如果点击的是豌豆卡片且太阳数足够
            {
                mciSendString("close button", NULL, 0, NULL);
                mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
                mciSendString("play button", NULL, 0, NULL);
                show_bean = 1;          //显示植物图片
                is_bean_move = 1;           //植物可以移动
                sun_num = sun_num - 100;            //花费100太阳数
                is_choose = 1;          //避免点击一个卡牌后还能点击别的卡牌
            }

            else if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= 192 && mouse_plant.x <= 267 &&
                mouse_plant.y >= 5 && mouse_plant.y <= 120 && sun_num >= 50
                && is_choose ==0)         //如果点击的是向日葵卡片且太阳数足够
            {
                mciSendString("close button", NULL, 0, NULL);
                mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
                mciSendString("play button", NULL, 0, NULL);
                show_sunflower = 1;         //显示植物图片
                is_sunflower_move = 1;          //植物可以移动
                sun_num = sun_num - 50;         //花费50太阳数
                is_choose = 1;
            }

            else if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= 279 && mouse_plant.x <= 354 &&
                mouse_plant.y >= 5 && mouse_plant.y <= 120 && sun_num >= 500        //如果点击的是坚果卡片且太阳数足够
                && is_choose == 0)
            {
                mciSendString("close button", NULL, 0, NULL);
                mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
                mciSendString("play button", NULL, 0, NULL);
                show_nut = 1;         //显示植物图片
                is_nut_move = 1;          //植物可以移动
                sun_num = sun_num - 500;         //花费500太阳数
                is_choose = 1;
            }

            else if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= 366 && mouse_plant.x <= 426 &&
                mouse_plant.y >= 5 && mouse_plant.y <= 120          //如果点击了铲子
                && is_choose ==0)         
            {
                mciSendString("close button", NULL, 0, NULL);
                mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
                mciSendString("play button", NULL, 0, NULL);
                is_shovel = 1;         
                is_shovel_move = 1;          
                is_choose = 1;
            }

            //豌豆的种植
            if (is_bean_move == 1)          //如果豌豆可以移动
            {
                if (mouse_plant.uMsg == WM_MOUSEMOVE)           //获取鼠标如何移动的消息，让豌豆图片跟随鼠标移动
                {
                    bean_x = mouse_plant.x;
                    bean_y = mouse_plant.y;
                }
                for (i = 0; i < 9; i++)         //遍历所有方块
                {
                    for (j = 0; j < 5; j++)
                    {
                        if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= (375 + size_width * i) &&
                            mouse_plant.x <= (375 + size_width * (i + 1)) &&
                            mouse_plant.y >= (135 + size_high * j) && mouse_plant.y <= (135 + size_high * (j + 1))
                            && map[i][j] == 0)
                            //记录种植（鼠标点击）的是哪一块
                        {
                            mciSendString("close plant", NULL, 0, NULL);
                            mciSendString("open ./plant.mp3 alias plant", NULL, 0, NULL);
                            mciSendString("play plant", NULL, 0, NULL);
                            is_bean_move = 0;           //不能移动
                            is_planted = 1;         //已完成种植
                            map[i][j] = 1;          //对这一方块进行标记
                        }
                    }
                }
            }

            //向日葵的种植
            if (is_sunflower_move == 1)         //如果向日葵可以移动
            {
                if (mouse_plant.uMsg == WM_MOUSEMOVE)           //获取鼠标如何移动的消息，让向日葵图片跟随鼠标移动
                {
                    sunflower_x = mouse_plant.x;
                    sunflower_y = mouse_plant.y;
                }
                for (i = 0; i < 9; i++)         //遍历所有方块
                {
                    for (j = 0; j < 5; j++)
                    {
                        if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= (375 + size_width * i) &&
                            mouse_plant.x <= (375 + size_width * (i + 1)) &&
                            mouse_plant.y >= (135 + size_high * j) && mouse_plant.y <= (135 + size_high * (j + 1))
                            && map[i][j] == 0)
                            //记录种植（鼠标点击）的是哪一块
                        {
                            mciSendString("close plant", NULL, 0, NULL);
                            mciSendString("open ./plant.mp3 alias plant", NULL, 0, NULL);
                            mciSendString("play plant", NULL, 0, NULL);
                            is_sunflower_move = 0;          //不能移动
                            is_planted = 1;         //已完成种植
                            map[i][j] = 2;          //对这一方块进行标记
                        }
                    }
                }
            }

            //坚果的种植
            if (is_nut_move == 1)          //如果豌豆可以移动
            {
                if (mouse_plant.uMsg == WM_MOUSEMOVE)           //获取鼠标如何移动的消息，让豌豆图片跟随鼠标移动
                {
                    nut_x = mouse_plant.x;
                    nut_y = mouse_plant.y;
                }
                for (i = 0; i < 9; i++)         //遍历所有方块
                {
                    for (j = 0; j < 5; j++)
                    {
                        if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= (375 + size_width * i) &&
                            mouse_plant.x <= (375 + size_width * (i + 1)) &&
                            mouse_plant.y >= (135 + size_high * j) && mouse_plant.y <= (135 + size_high * (j + 1))
                            && map[i][j] == 0)
                            //记录种植（鼠标点击）的是哪一块
                        {
                            mciSendString("close plant", NULL, 0, NULL);
                            mciSendString("open ./plant.mp3 alias plant", NULL, 0, NULL);
                            mciSendString("play plant", NULL, 0, NULL);
                            is_nut_move = 0;           //不能移动
                            is_planted = 1;         //已完成种植
                            map[i][j] = 3;          //对这一方块进行标记
                        }
                    }
                }
            }

            if (is_shovel_move == 1)            //让铲子跟随鼠标移动而移动
            {
                if (mouse_plant.uMsg == WM_MOUSEMOVE)
                {
                    shovel_x = mouse_plant.x;
                    shovel_y = mouse_plant.y;
                }
                for (i = 0; i < 9; i++)         //遍历所有方块
                {
                    for (j = 0; j < 5; j++)
                    {
                        if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= (375 + size_width * i) &&
                            mouse_plant.x <= (375 + size_width * (i + 1)) &&
                            mouse_plant.y >= (135 + size_high * j) && mouse_plant.y <= (135 + size_high * (j + 1)))
                            //记录种植（鼠标点击）的是哪一块
                        {
                            mciSendString("close shovel", NULL, 0, NULL);
                            mciSendString("open ./shovel.mp3 alias shovel", NULL, 0, NULL);
                            mciSendString("play shovel", NULL, 0, NULL);

                            is_shovel_move = 0;          //不能移动
                            map[i][j] = 0;          //对这一方块进行标记
                            is_planted = 1;
                        }
                    }
                }
            }

            if (is_planted == 1)            //重新初始化参数使能够进行多次种植
            {
                is_planted = 0;
                bean_x = 105;
                bean_y = 5;
                sunflower_x = 192;
                sunflower_y = 5;
                nut_x = 279;
                nut_y = 5;
                shovel_x = 279;
                shovel_y = 5;
                show_bean = 0;
                show_sunflower = 0;
                show_nut = 0;
                is_shovel = 0;
                is_choose = 0;
            }

            if (mouse_plant.uMsg == WM_LBUTTONDOWN && mouse_plant.x >= sun_x && mouse_plant.x <= sun_x + 60 &&
                mouse_plant.y >= sun_y && mouse_plant.y <= sun_y + 60)          //如果太阳图片被点击，重新初始化太阳坐标，并增加太阳数
            {
                mciSendString("close sun_msc", NULL, 0, NULL);
                mciSendString("open ./sun.mp3 alias sun_msc", NULL, 0, NULL);
                mciSendString("play sun_msc", NULL, 0, NULL);

                sun_x = rand() % (game_width - 375) + 375;          //随机产生太阳的横坐标
                sun_y = -400;
                sun_num = sun_num + 50;
            }
        }
    }
    //实现暂停功能
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == 27)            //Esc键的ASCII码是27
        {
            mciSendString("close button", NULL, 0, NULL);
            mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
            mciSendString("play button", NULL, 0, NULL);

            mciSendString("close wahu", NULL, 0, NULL);
            mciSendString("open ./wahu.mp3 alias wahu", NULL, 0, NULL);
            mciSendString("play wahu", NULL, 0, NULL);
            gamestatus = 3;
        }
    }
}

void gameover()
{
    EndBatchDraw();         //结束批量绘图
    _getch();
    closegraph();
}

void pause_menu()
{
    char input;         //继续游戏
    if (kbhit())
    {
        input = getch();
        if (input == '1')
        {
            mciSendString("close button", NULL, 0, NULL);
            mciSendString("open ./button.mp3 alias button", NULL, 0, NULL);
            mciSendString("play button", NULL, 0, NULL);
            gamestatus = 1;
        }
    }

    setbkmode(TRANSPARENT);         //提醒开始的小提示
    settextstyle(120, 0, "黑体");
    setcolor(BLACK);
    char ch[15] = "按\"1\"继续游戏";            //双引号前加上反斜杠（\）可以在字符串中添加双引号
    int ch_x = (1200 - textwidth(ch)) / 2;
    int ch_y = 300;
    outtextxy(ch_x, ch_y, ch);

    putimage(0, 240, &dave_s, NOTSRCERASE);        //显示戴夫
    putimage(0, 240, &dave, SRCINVERT);

    FlushBatchDraw();
}

void Game_gg()
{
    putimage(0, 0, &game_gg);           //加载游戏失败背景

    char input;         //键盘输入“1”关闭游戏
    if (kbhit())
    {
        input = getch();
        if (input == '1')
        {
            exit(0);            //关闭画面窗口函数
        }
    }

    setbkmode(TRANSPARENT);         //退出游戏的小提示
    settextstyle(120, 0, "黑体");
    setcolor(BLACK);
    char ch[15] = "按\"1\" 退出游戏";            //双引号前加上反斜杠（\）可以在字符串中添加双引号
    int ch_x = (1200 - textwidth(ch)) / 2;
    int ch_y = 300;
    outtextxy(ch_x, ch_y, ch);

    FlushBatchDraw();           //进行一次绘图
}

void Game_nice()
{
    putimage(300, 110, &victory1, NOTSRCERASE);           //加载游戏胜利背景
    putimage(300, 110, &victory2, SRCINVERT);

    char input;         //键盘输入“1”关闭游戏
    if (kbhit())
    {
        input = getch();
        if (input == '1')
            exit(0);            //关闭画面窗口函数
    }

    setbkmode(TRANSPARENT);         //退出游戏的小提示
    settextstyle(45, 0, "黑体");
    setcolor(BLACK);
    char ch[15] = "按\"1\" 退出游戏";            //双引号前加上反斜杠（\）可以在字符串中添加双引号
    int ch_x = (1200 - textwidth(ch)) / 2 - 70;
    int ch_y = 180;
    outtextxy(ch_x, ch_y, ch);

    FlushBatchDraw();           //进行一次绘图
}