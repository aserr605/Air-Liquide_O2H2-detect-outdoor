/*亞東路竹新廠 室外O2H2偵測控制箱體
 * 20220704
 *
 *20220712
 *更改前:警報時不能解除蜂鳴BUG。
 *更改後:警報後可以解除蜂鳴
 */
 //o2系統異常
const int o2_system_alarm = A0;
//o2測值異常
const int o2_alarm = A1;
//o2蜂鳴解除
const int btn_o2_release = 2;
//o2測試鈕
const int btn_o2_led_test = 3;
//o2蜂鳴器
const int o2_bee = 4;
//o2紅(測值)
const int led_o2_red = 5;
//o2黃(系統)
const int led_o2_yellow = 6;
//o2綠
const int led_o2_green = 7;
//H2系統異常
const int H2_system_alarm = A2;
//H2測值異常
const int H2_alarm = A3;
//H2蜂鳴解除
const int btn_H2_release = 8;
//H2測試鈕
const int btn_H2_led_test = 9;
//H2蜂鳴器
const int H2_bee = 10;
//H2紅(測值)
const int led_H2_red = 11;
//H2黃(系統)
const int led_H2_yellow = 12;
//H2綠
const int led_H2_green = 13;
/*  測試鈕                 btn_o2_led_test(1)     3
    蜂鳴解除                btn_o2_release(1)     2
    系統異常訊號            o2_system_alarm(1)     A2
    測值異常                o2_alarm(1)    A3*/
    /* 綠 黃(系統) 紅(測值)蜂鳴器
              1    1     1     1*/
int o2_s1 = 0;
int H2_s1 = 0;
bool o2b =false;
bool H2b = false;

void setup() {

    //Serial.begin(9600);
    pinMode(H2_alarm, INPUT);
    pinMode(H2_system_alarm, INPUT);
    pinMode(o2_alarm, INPUT);
    pinMode(o2_system_alarm, INPUT);
    pinMode(btn_H2_release, INPUT);
    pinMode(btn_H2_led_test, INPUT);
    pinMode(btn_o2_release, INPUT);
    pinMode(btn_o2_led_test, INPUT);

    pinMode(H2_bee, OUTPUT);
    pinMode(o2_bee, OUTPUT);

    pinMode(led_o2_red, OUTPUT);
    pinMode(led_o2_green, OUTPUT);
    pinMode(led_o2_yellow, OUTPUT);
    pinMode(led_H2_red, OUTPUT);
    pinMode(led_H2_green, OUTPUT);
    pinMode(led_H2_yellow, OUTPUT);

    analogWrite(btn_o2_led_test, 0);//需要初始化不然電壓不穩定
    analogWrite(btn_H2_led_test, 0);//需要初始化不然電壓不穩定
    analogWrite(H2_alarm, 0);//需要初始化不然電壓不穩定
    analogWrite(o2_alarm, 0);//需要初始化不然電壓不穩定
    analogWrite(H2_system_alarm, 0);
    analogWrite(o2_system_alarm, 0);

    digitalWrite(o2_bee, LOW);
    digitalWrite(led_o2_green, LOW);
    digitalWrite(led_o2_red, LOW);
    digitalWrite(led_o2_yellow, LOW);


    digitalWrite(H2_bee, LOW);
    digitalWrite(led_H2_green, LOW);
    digitalWrite(led_H2_red, LOW);
    digitalWrite(led_H2_yellow, LOW);

}

void loop() {



    if (digitalRead(btn_o2_led_test) == HIGH)//測試鈕
    {
        /* 綠 黃(系統) 紅(測值)蜂鳴器
         1     1     1     1*/
        o2_s1 = 15;
        //Serial.println("/if (digitalRead( btn_o2_led_test)==HIGH)//測試鈕");

    }
    else if (analogRead(o2_system_alarm) > 512)//系統異常訊號
    {
        if (digitalRead(btn_o2_release) == HIGH)//測值異常蜂鳴解除 
        {
            //Serial.println("if (digitalRead(btn_o2_release)==HIGH)//測值異常蜂鳴解除 ");
            o2b = true;

        }
        if (o2b == true)
        {
            o2_s1 = 4;
        }
        else
        {
            o2_s1 = 5;
        }
    }
    else if (analogRead(o2_alarm) > 512)//測值異常
    {
       
        if (digitalRead(btn_o2_release) == HIGH)//測值異常蜂鳴解除 
        {
            //Serial.println("if (digitalRead(btn_o2_release)==HIGH)//測值異常蜂鳴解除 ");
            o2b = true;
           
        }
        if (o2b==true)
        {
            o2_s1 = 2;
        }
        else
        {
            o2_s1 = 3;
        }
        
        //Serial.println("if (analogRead(o2_alarm) > 512)//測值異常");
    }
    else
    {
        o2b = false;
        o2_s1 = 8;
    }
    //Serial.println("o2_test: ");
    //Serial.println(digitalRead(btn_o2_led_test));
    //Serial.println("o2_release: ");
    //Serial.println(digitalRead(btn_o2_release));
    //Serial.println("o2_system: ");
    //Serial.println(analogRead(o2_system_alarm));
    //Serial.println("o2_alarm: ");
    //Serial.println(analogRead(o2_alarm));
    //Serial.println("o2_s1");
    //Serial.println(o2_s1);

    switch (o2_s1)
    {
        //Serial.println("switch");
    case 15:
        LED_control_o2(HIGH, HIGH, HIGH, HIGH);//測試鈕
        break; //Serial.println("LED_control_o2(HIGH, HIGH, HIGH, HIGH);//測試鈕");
    case 5:
        LED_control_o2(LOW, HIGH, LOW, HIGH);//系統異常訊號
        break;
    case 3:
        LED_control_o2(LOW, LOW, HIGH, HIGH);//測值異常
        break;
    case 4:
        LED_control_o2(LOW, HIGH, LOW, LOW);//系統異常蜂鳴解除
        break;
    case 2:
        LED_control_o2(LOW, LOW, HIGH, LOW);//測值異常蜂鳴解除
        break;
    case 8:
        LED_control_o2(HIGH, LOW, LOW, LOW);//恢復正常
        break;
    };

    //=========================================================================
    if (digitalRead(btn_H2_led_test) == HIGH)//測試鈕
    {
        /* 綠 黃(系統) 紅(測值)蜂鳴器
         1     1     1     1*/
        H2_s1 = 15;
        //Serial.println("/if (digitalRead( btn_H2_led_test)==HIGH)//測試鈕");

    }
    else if (analogRead(H2_system_alarm) > 512)//系統異常訊號
    {
        if (digitalRead(btn_H2_release) == HIGH)//測值異常蜂鳴解除 
        {
            //Serial.println("if (digitalRead(btn_H2_release)==HIGH)//測值異常蜂鳴解除 ");
            H2b = true;

        }
        if (H2b == true)
        {
            H2_s1 = 4;
        }
        else
        {
            H2_s1 = 5;
        }
    }
    else if (analogRead(H2_alarm) > 512)//測值異常
    {

        if (digitalRead(btn_H2_release) == HIGH)//測值異常蜂鳴解除 
        {
            //Serial.println("if (digitalRead(btn_H2_release)==HIGH)//測值異常蜂鳴解除 ");
            H2b = true;

        }
        if (H2b == true)
        {
            H2_s1 = 2;
        }
        else
        {
            H2_s1 = 3;
        }

        //Serial.println("if (analogRead(H2_alarm) > 512)//測值異常");
    }
    else
    {
        H2b = false;
        H2_s1 = 8;
    }
    //Serial.println("H2_test: ");
    //Serial.println(digitalRead(btn_H2_led_test));
    //Serial.println("H2_release: ");
    //Serial.println(digitalRead(btn_H2_release));
    //Serial.println("H2_system: ");
    //Serial.println(analogRead(H2_system_alarm));
    //Serial.println("H2_alarm: ");
    //Serial.println(analogRead(H2_alarm));
    //Serial.println("H2_s1");
    //Serial.println(H2_s1);

    switch (H2_s1)
    {
        //Serial.println("switch");
    case 15:
        LED_control_H2(HIGH, HIGH, HIGH, HIGH);//測試鈕
        break; //Serial.println("LED_control_H2(HIGH, HIGH, HIGH, HIGH);//測試鈕");
    case 5:
        LED_control_H2(LOW, HIGH, LOW, HIGH);//系統異常訊號
        break;
    case 3:
        LED_control_H2(LOW, LOW, HIGH, HIGH);//測值異常
        break;
    case 4:
        LED_control_H2(LOW, HIGH, LOW, LOW);//系統異常蜂鳴解除
        break;
    case 2:
        LED_control_H2(LOW, LOW, HIGH, LOW);//測值異常蜂鳴解除
        break;
    case 8:
        LED_control_H2(HIGH, LOW, LOW, LOW);//恢復正常
        break;
    };




}
//綠 黃(系統) 紅(測值)蜂鳴器
void LED_control_o2(word o2_1, word o2_2, word o2_3, word o2_4)
{
    o2_green(o2_1);
    o2_alarm_yellow(o2_2);
    o2_alarm_red(o2_3);
    o2_alarm_bee(o2_4);

}
void o2_green(word y1)
{
    digitalWrite(led_o2_green, y1);
}
void o2_alarm_yellow(word y2)
{
    digitalWrite(led_o2_yellow, y2);
}
void o2_alarm_red(word y3)
{
    digitalWrite(led_o2_red, y3);
}
void o2_alarm_bee(word y4)
{
    digitalWrite(o2_bee, y4);
}

void LED_control_H2(word H2_1, word H2_2, word H2_3, word H2_4)
{
    H2_green(H2_1);
    H2_alarm_yellow(H2_2);
    H2_alarm_red(H2_3);
    H2_alarm_bee(H2_4);

}
void H2_green(word x1)
{
    digitalWrite(led_H2_green, x1);
}
void H2_alarm_yellow(word x2)
{
    digitalWrite(led_H2_yellow, x2);
}
void H2_alarm_red(word x3)
{
    digitalWrite(led_H2_red, x3);
}
void H2_alarm_bee(word x4)
{
    digitalWrite(H2_bee, x4);
}
