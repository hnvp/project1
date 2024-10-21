#include <TimerOne.h>

int DATA  = 10;
int CK    = 11;
int EN    = 12;

int XANH_NGANG  = 5;
int VANG_NGANG  = 6;
int DO_NGANG    = 7;

int XANH_DOC  = 4;
int VANG_DOC  = 3;
int DO_DOC    = 2;

int RE_NGANG  = 8;
int RE_DOC    = 9;

int BINH_THUONG = A1;
int CAO_DIEM    = A0;
int BAN_DEM     = A2;
int CHUYEN      = A3;

int ma7doan[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90 };
int led0, led1, led2, led3, led4, led5, led6, led7;
int tt_ngang, tt_doc;
int xanh_ngang, re_ngang, vang_ngang, do_ngang, xanh_doc, re_doc, vang_doc, do_doc;
int gh_xanh_ngang, gh_re_ngang, gh_vang_ngang, gh_do_ngang;
int gh_xanh_doc, gh_re_doc, gh_vang_doc,  gh_do_doc;

int ngat, tt_kich, tt_chuyen;

void xuat1byte(int x) {
  int d, i;
  d = x;
  for (i = 0; i < 8; i++) {
    if ((d & 0x80) == 0x80) digitalWrite(DATA, HIGH);
    else                    digitalWrite(DATA, LOW);
    digitalWrite(CK, HIGH);   delayMicroseconds(5);
    digitalWrite(CK, LOW);    delayMicroseconds(5);
    d = d << 1;
  }
}

void xuat2so(int l1, int l0) {
  xuat1byte(l1);
  xuat1byte(l0);
  digitalWrite(EN, HIGH);   delayMicroseconds(5);
  digitalWrite(EN, LOW);    delayMicroseconds(5);
}

void hienthi(int lap) {
  int dem;
  for (dem = 0; dem < lap; dem++) {
    xuat2so(led0, 0xfe);  delay(1);   xuat2so(led0, 0xff);
    xuat2so(led1, 0xfd);  delay(1);   xuat2so(led1, 0xff);
    xuat2so(led2, 0xfb);  delay(1);   xuat2so(led2, 0xff);
    xuat2so(led3, 0xf7);  delay(1);   xuat2so(led3, 0xff);
    xuat2so(led4, 0xef);  delay(1);   xuat2so(led4, 0xff);
    xuat2so(led5, 0xdf);  delay(1);   xuat2so(led5, 0xff);
    xuat2so(led6, 0xbf);  delay(1);   xuat2so(led6, 0xff);
    xuat2so(led7, 0x7f);  delay(1);   xuat2so(led7, 0xff);
  }
}

void kt_nut_nhan() {
  if (digitalRead(BINH_THUONG) == 0) {
    tt_kich = 0;
    tt_ngang = 0;
    tt_doc = 0;
    gh_xanh_ngang = 12;      gh_re_ngang = 12;    gh_vang_ngang = 3;    gh_do_ngang = 15; 
    gh_xanh_doc   = 12;      gh_re_doc   = 12;    gh_vang_doc   = 3;    gh_do_doc   = 15; 
    xanh_ngang = gh_xanh_ngang;   re_ngang = gh_re_ngang;   vang_ngang = gh_vang_ngang;   do_ngang = gh_do_ngang;
    xanh_doc   = gh_xanh_doc;     re_doc   = gh_re_doc;     vang_doc   = gh_vang_doc;     do_doc   = gh_do_doc;    
  }
  else if (digitalRead(CAO_DIEM) == 0) {
    tt_kich = 1;
    tt_chuyen = 0;
    led0 = 0xff;
    led1 = 0xff;
    led2 = 0xff;
    led3 = 0xff;
    led4 = 0xff;
    led5 = 0xff;
    led6 = 0xff;
    led7 = 0xff;
    digitalWrite(XANH_NGANG,  LOW);
    digitalWrite(RE_NGANG,    LOW);
    digitalWrite(VANG_NGANG,  HIGH);
    digitalWrite(DO_NGANG,    LOW);
    digitalWrite(XANH_DOC,    LOW);
    digitalWrite(RE_DOC,      LOW);
    digitalWrite(VANG_DOC,    HIGH);
    digitalWrite(DO_DOC,      LOW);    
    delay(3000);
    digitalWrite(XANH_NGANG,  HIGH);
    digitalWrite(RE_NGANG,    HIGH);
    digitalWrite(VANG_NGANG,  LOW);
    digitalWrite(DO_NGANG,    LOW);
    digitalWrite(XANH_DOC,    LOW);
    digitalWrite(RE_DOC,      LOW);
    digitalWrite(VANG_DOC,    LOW);
    digitalWrite(DO_DOC,      HIGH);
    while (digitalRead(CAO_DIEM) == 0);
  }
  else if (digitalRead(BAN_DEM) == 0) {
    tt_kich = 2;
    led0 = 0xff;
    led1 = 0xff;
    led2 = 0xff;
    led3 = 0xff;
    led4 = 0xff;
    led5 = 0xff;
    led6 = 0xff;
    led7 = 0xff;
  }
}

void kt_chuyen() {
  if (digitalRead(CHUYEN) == 0) {
    delay(20);
    if (digitalRead(CHUYEN) == 0) {
      tt_chuyen++;
      if (tt_chuyen > 1) tt_chuyen = 0;
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  HIGH);
      digitalWrite(DO_NGANG,    LOW);
      digitalWrite(XANH_DOC,    LOW);
      digitalWrite(RE_DOC,      LOW);
      digitalWrite(VANG_DOC,    HIGH);
      digitalWrite(DO_DOC,      LOW);      
      delay(3000);
      if (tt_chuyen == 0) {
        digitalWrite(XANH_NGANG,  HIGH);
        digitalWrite(RE_NGANG,    HIGH);
        digitalWrite(VANG_NGANG,  LOW);
        digitalWrite(DO_NGANG,    LOW);
        digitalWrite(XANH_DOC,    LOW);
        digitalWrite(RE_DOC,      LOW);
        digitalWrite(VANG_DOC,    LOW);
        digitalWrite(DO_DOC,      HIGH);
      } else {
        digitalWrite(XANH_NGANG,  LOW);
        digitalWrite(RE_NGANG,    LOW);
        digitalWrite(VANG_NGANG,  LOW);
        digitalWrite(DO_NGANG,    HIGH);
        digitalWrite(XANH_DOC,    HIGH);
        digitalWrite(RE_DOC,      HIGH);
        digitalWrite(VANG_DOC,    LOW);
        digitalWrite(DO_DOC,      LOW);  
      }
    }
  }
}

void dem_nguoc_ngang() {
  if (tt_ngang == 0) {
    if (xanh_ngang > 0) {
      xanh_ngang--;
      led0 = ma7doan[xanh_ngang / 10];
      led1 = ma7doan[xanh_ngang % 10];
      led2 = ma7doan[xanh_ngang / 10];
      led3 = ma7doan[xanh_ngang % 10];
      digitalWrite(XANH_NGANG,  HIGH);
      digitalWrite(RE_NGANG,    HIGH);
      digitalWrite(VANG_NGANG,  LOW);
      digitalWrite(DO_NGANG,    LOW);
    } else {
      xanh_ngang = gh_xanh_ngang;
      vang_ngang = gh_vang_ngang;
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  HIGH);
      digitalWrite(DO_NGANG,    LOW);
      tt_ngang = 1;
    }
  } else if (tt_ngang == 1) {
    if (vang_ngang > 0) {
      vang_ngang--;
      led0 = ma7doan[vang_ngang / 10];
      led1 = ma7doan[vang_ngang % 10];
      led2 = ma7doan[vang_ngang / 10];
      led3 = ma7doan[vang_ngang % 10];
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  HIGH);
      digitalWrite(DO_NGANG,    LOW);
    } else {
      do_ngang = gh_do_ngang;
      vang_ngang = gh_vang_ngang;
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  LOW);
      digitalWrite(DO_NGANG,    HIGH);
      tt_ngang = 2;
    }
  } else if (tt_ngang == 2) {
    if (do_ngang > 0) {
      do_ngang--;
      led0 = ma7doan[do_ngang / 10];
      led1 = ma7doan[do_ngang % 10];
      led2 = ma7doan[do_ngang / 10];
      led3 = ma7doan[do_ngang % 10];
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  LOW);
      digitalWrite(DO_NGANG,    HIGH);
    } else {
      do_ngang = gh_do_ngang;
      re_ngang = gh_re_ngang;
      digitalWrite(XANH_NGANG,  HIGH);
      digitalWrite(RE_NGANG,    HIGH);
      digitalWrite(VANG_NGANG,  LOW);
      digitalWrite(DO_NGANG,    LOW);
      tt_ngang = 0;
    }
  }
}

void dem_nguoc_doc() {
  if (tt_doc == 0) {
    if (do_doc > 0) {
      do_doc--;
      led4 = ma7doan[do_doc / 10];
      led5 = ma7doan[do_doc % 10];
      led6 = ma7doan[do_doc / 10];
      led7 = ma7doan[do_doc % 10];
      digitalWrite(XANH_DOC,  LOW);
      digitalWrite(RE_DOC,    LOW);
      digitalWrite(VANG_DOC,  LOW);
      digitalWrite(DO_DOC,    HIGH);
    } else {
      do_doc = gh_do_doc;
      re_doc = gh_re_doc;
      led4 = ma7doan[xanh_doc / 10];
      led5 = ma7doan[xanh_doc % 10];
      led6 = ma7doan[xanh_doc / 10];
      led7 = ma7doan[xanh_doc % 10];
      digitalWrite(XANH_DOC,  HIGH);
      digitalWrite(RE_DOC,    HIGH);
      digitalWrite(VANG_DOC,  LOW);
      digitalWrite(DO_DOC,    LOW);
      tt_doc = 1;
    }
  } else if (tt_doc == 1) {
    if (xanh_doc > 0) {
      xanh_doc--;
      led4 = ma7doan[xanh_doc / 10];
      led5 = ma7doan[xanh_doc % 10];
      led6 = ma7doan[xanh_doc / 10];
      led7 = ma7doan[xanh_doc % 10];
      digitalWrite(XANH_DOC,  HIGH);
      digitalWrite(RE_DOC,    HIGH);
      digitalWrite(VANG_DOC,  LOW);
      digitalWrite(DO_DOC,    LOW);
    } else {
      vang_doc = gh_vang_doc;
      xanh_doc = gh_xanh_doc;
      led4 = ma7doan[vang_doc / 10];
      led5 = ma7doan[vang_doc % 10];
      led6 = ma7doan[vang_doc / 10];
      led7 = ma7doan[vang_doc % 10];
      digitalWrite(XANH_DOC,  LOW);
      digitalWrite(RE_DOC,    LOW);
      digitalWrite(VANG_DOC,  HIGH);
      digitalWrite(DO_DOC,    LOW);
      tt_doc = 2;
    }
  } else if (tt_doc == 2) {
    if (vang_doc > 0) {
      vang_doc--;
      led4 = ma7doan[vang_doc / 10];
      led5 = ma7doan[vang_doc % 10];
      led6 = ma7doan[vang_doc / 10];
      led7 = ma7doan[vang_doc % 10];
      digitalWrite(XANH_DOC,  LOW);
      digitalWrite(RE_DOC,    LOW);
      digitalWrite(VANG_DOC,  HIGH);
      digitalWrite(DO_DOC,    LOW);
    } else {
      vang_doc = gh_vang_doc;
      do_doc = gh_do_doc;
      led4 = ma7doan[do_doc / 10];
      led5 = ma7doan[do_doc % 10];
      led6 = ma7doan[do_doc / 10];
      led7 = ma7doan[do_doc % 10];
      digitalWrite(XANH_DOC,  LOW);
      digitalWrite(RE_DOC,    LOW);
      digitalWrite(VANG_DOC,  LOW);
      digitalWrite(DO_DOC,    HIGH);
      tt_doc = 0;
    }
  }
}

void dem_thoi_gian() {
  if (tt_kich == 0) {
    ngat++;
    if (ngat >= 10) {
      dem_nguoc_ngang();
      dem_nguoc_doc();
      ngat = 0;
    }
  }
  else if (tt_kich == 2) {
    ngat++;
    if (ngat < 5) {
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  LOW);
      digitalWrite(DO_NGANG,    LOW);
      digitalWrite(XANH_DOC,    LOW);
      digitalWrite(RE_DOC,      LOW);
      digitalWrite(VANG_DOC,    LOW);
      digitalWrite(DO_DOC,      LOW);
    } else if (ngat < 9) {
      digitalWrite(XANH_NGANG,  LOW);
      digitalWrite(RE_NGANG,    LOW);
      digitalWrite(VANG_NGANG,  HIGH);
      digitalWrite(DO_NGANG,    LOW);
      digitalWrite(XANH_DOC,    LOW);
      digitalWrite(RE_DOC,      LOW);
      digitalWrite(VANG_DOC,    HIGH);
      digitalWrite(DO_DOC,      LOW);
    } else {
      ngat = 0;
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(DATA, OUTPUT);
  pinMode(CK,   OUTPUT);
  pinMode(EN,   OUTPUT);

  pinMode(XANH_NGANG, OUTPUT);
  pinMode(VANG_NGANG, OUTPUT);
  pinMode(DO_NGANG,   OUTPUT);

  pinMode(XANH_DOC, OUTPUT);
  pinMode(VANG_DOC, OUTPUT);
  pinMode(DO_DOC,   OUTPUT);

  pinMode(RE_NGANG, OUTPUT);
  pinMode(RE_DOC,   OUTPUT);
  
  pinMode(BINH_THUONG,  INPUT);
  pinMode(CAO_DIEM,     INPUT);
  pinMode(BAN_DEM,      INPUT);
  pinMode(CHUYEN,       INPUT);

  ngat = 0;
  tt_kich = 0;
  tt_ngang = 0;
  tt_doc = 0;
  gh_xanh_ngang = 12;      gh_re_ngang = 12;    gh_vang_ngang = 3;    gh_do_ngang = 15; 
  gh_xanh_doc   = 12;      gh_re_doc   = 12;    gh_vang_doc   = 3;    gh_do_doc   = 15; 
  xanh_ngang = gh_xanh_ngang;   re_ngang = gh_re_ngang;   vang_ngang = gh_vang_ngang;   do_ngang = gh_do_ngang;
  xanh_doc   = gh_xanh_doc;     re_doc   = gh_re_doc;     vang_doc   = gh_vang_doc;     do_doc   = gh_do_doc;    
  Timer1.initialize(100000);
  Timer1.attachInterrupt(dem_thoi_gian);

  digitalWrite(XANH_NGANG,  LOW);
  digitalWrite(RE_NGANG,    LOW);
  digitalWrite(VANG_NGANG,  LOW);
  digitalWrite(DO_NGANG,    LOW);
  digitalWrite(XANH_DOC,    LOW);
  digitalWrite(RE_DOC,      LOW);
  digitalWrite(VANG_DOC,    LOW);
  digitalWrite(DO_DOC,      LOW);

  led0 = 0xff;
  led1 = 0xff;
  led2 = 0xff;
  led3 = 0xff;
  led4 = 0xff;
  led5 = 0xff;
  led6 = 0xff;
  led7 = 0xff;
  hienthi(1);
}

void loop() {
  hienthi(2);
  kt_nut_nhan();
  if (tt_kich == 1) {
    kt_chuyen();
  }
}