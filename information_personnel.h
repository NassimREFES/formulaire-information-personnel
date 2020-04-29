#ifndef INFORMATION_PERSONNEL
#define INFORMATION_PERSONNEL

#include <wx/wx.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/spinctrl.h>
#include <wx/srchctrl.h>
#include <wx/wfstream.h>
#include <wx/sizer.h>
#include <wx/datectrl.h>
#include <wx/calctrl.h>
#include <wx/textfile.h>
#include <wx/listctrl.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <clocale>

using namespace std;

enum {
	//G1
	nom_prenom = 0, date_naissance, adresse, telephone, nationalite,
	num_piece_identite, email, age, sex, poid, taille, vue, groupe_sanguin,
	signe_speciaux, test_medical,

	//G2
	num_dossier, annee_entrainement, num_piece, date_inscription,

	//G3
	grade_scolair_sportif, grade_scolair, num_institution,
	adresse_institution, prof_institution, num_prof,
	nom_pere, telephone_pere, relation_parent, face_relation_parent,

	//G4
	n_actuel, n_precedent, sport_pratique, specialite, specialite_precise, 
	face_specialite, blessur_precedent, profession

};

const vector<wxString> langue_francais = { 
// G1
	wxT("الإسم و اللقب"),
	wxT("مكان الإزدياد "),
	wxT("العنوان"),
	wxT("الهاتف"),
	wxT("الجنسية"),
	wxT("رقم ب ت و"),
	wxT(" @ الإميل"),
	wxT("السن"),
	wxT("الجنس"),
	wxT("الوزن"),
	wxT("القامة"), 
	wxT("النظر"),
	wxT("زمرة الدم"),
	wxT("علامات الخصوصية"),
	wxT("فحص الطبي"),
// G2
	wxT("numero dossier"),
	wxT("annee entrainement"),
	wxT("numero piece"),
	wxT("date inscription"),
// G3
	wxT("مستوى الدراسي"), 
	wxT("المؤسسة الدراسية"),
	wxT("هاتف المؤسسة"),
	wxT("عنوان المؤسسة"),
	wxT("الإسم و اللقب أستاذ التربية البدنية"),
	wxT("هاتف أستاذ"),
	wxT("إسم الأب"),
	wxT("هاتف الأب"),
	wxT("الحالة الإجتماعية للأبوين"),
// G4
	wxT("النادي الحالي"),
	wxT("النادي السابق"),
	wxT("الرياضة"),
	wxT("إختصاص"),
	wxT("إختصاص الدقيق"),
	wxT("الفئة العمرية"),
	wxT("إصابات السابقة"),
};

const vector<wxString> kk = {
	wxT("رقم الملف"),
	wxT("رقم الرخصة"),
	wxT("السنة التدريبية"),
	wxT("تاريخ تسجيل"),
	wxT("تاريخ الخروج")
};

const vector<short> ID_kk = {
	1001,
	1002,
	1003,
	1004,
	1005
};

const short ID_SPORT = 1010;
const short ID_SPECIALITE1 = 1011;
const short ID_SPECIALITE1_PRECISE = 1011;
const short ID_FACE_SPECIALITE = 1012;
const short ID_SITUATION_FAMILIALE = 1013;
const short ID_WILAYA = 1014;
const short ID_GRAD_SCOLAIR = 1015;
const short ID_SPECIALITE_ENTRAINEUR = 1016;
const short ID_AGE = 1017;

// tableau_liste
const short ID_VERIF	= 1018;
const short ID_IMPR		= 1019;
const short ID_PGP		= 1020;
const short ID_RCH		= 1021;

const wxString grad_scolair_list[6] = {
	wxT("إبتدائي "),
	wxT("متوسط "),
	wxT("ثانوي"),
	wxT("جامعي"),
	wxT("تعليم"),
	wxT("وتكوين مهني")
};

const wxString wilaya_list[48] = {
	wxT("1 ولاية أدرار"),
	wxT("2 ولاية الشلف"),
	wxT("3 ولاية الأغواط"),
	wxT("4 ولاية أم البواقي"),
	wxT("5 ولاية باتنة"),
	wxT("6 ولاية بجاية"),
	wxT("7 ولاية بسكرة"),
	wxT("8 ولاية بشار"),
	wxT("9 ولاية البليدة"),
	wxT("10 ولاية البويرة"),
	wxT("11 ولاية تمنراست"),
	wxT("12 ولاية تبسة"),
	wxT("13 ولاية تلمسان"),
	wxT("14 ولاية تيارت"),
	wxT("15 ولاية تيزي وزو"),
	wxT("16 ولاية الجزائر"),
	wxT("17 ولاية الجلفة"),
	wxT("18 ولاية جيجل"),
	wxT("19 ولاية سطيف"),
	wxT("20 ولاية سعيدة"),
	wxT("21 ولاية سكيكدة"),
	wxT("22 ولاية سيدي بلعباس"),
	wxT("23 ولاية عنابة"),
	wxT("24 ولاية قالمة"),
	wxT("25 ولاية قسنطينة"),
	wxT("26 ولاية المدية"),
	wxT("27 ولاية مستغانم"),
	wxT("28 ولاية المسيلة"),
	wxT("29 ولاية معسكر"),
	wxT("30 ولاية ورقلة"),
	wxT("31 ولاية وهران"),
	wxT("32 ولاية البيض"),
	wxT("33 ولاية إليزي"),
	wxT("34 ولاية برج بوعريريج"),
	wxT("35 ولاية بومرداس"),
	wxT("36 ولاية الطارف"),
	wxT("37 ولاية تندوف"),
	wxT("38 ولاية تيسمسيلت"),
	wxT("39 ولاية الوادي"),
	wxT("40 ولاية خنشلة"),
	wxT("41 ولاية سوق أهراس"),
	wxT("42 ولاية تيبازة"),
	wxT("43 ولاية ميلة"),
	wxT("44 ولاية عين الدفلى"),
	wxT("45 ولاية النعامة"),
	wxT("46 ولاية عين تموشنت"), 
	wxT("47 ولاية غرداية"),
	wxT("48 ولاية غليزان")
};

const wxString situation_familiale_list[4] = {
	wxT("أعزب"), 
	wxT("(متزوج(ة"),
	wxT("(مطلق(ة"),
	wxT("أرملة")
};

const wxString sports[9] = {
	wxT("الجمباز"),
	wxT("ألعاب القوى"),
	wxT("الكراتي دو"),
	wxT("الجيدو"),
	wxT("السباحة"),
	wxT("كرة اليد"),
	wxT("كرة السلة "),
	wxT("كرة الطائرة"),
	wxT("كرة القدم")
};

const wxString specialite_sport1[12] = {
	wxT("جهاز العقلة"),
	wxT("جمباز عام"),
	wxT("جمباز متخصص"),
	wxT("الترامبولين"),
	wxT("تامبلينغ"),
	wxT("جهاز المتوازي"),
	wxT("جهاز الحلق"),
	wxT("جهاز حصان الحلق"),
	wxT("جهاز منصة القفز"),
	wxT("عارضة التوازن"),
	wxT("حركات الأرضية"),
	wxT("جهاز متوازي مختلف الإرتفاع")
};

const wxString specialite_sport2[9] = {
	wxT("عدو المسافات القصيرة"),
	wxT("عدو المسافات المتوسطة"),
	wxT("عدو المسافات الطويلة"),
	wxT("عدو الحواجز"),
	wxT("عدو التتابع"),
	wxT("مشي  20 كم / مشي 50  كم"),
	wxT("القفز الطويل /القفز الثلاثي/القفز العالي/ القفز بالزانة"),
	wxT("رمي الجلة  / رمي القرص   /رمي الرمح  رمي المطرقة"),
	wxT("العشاري السباعي")
};

const wxString specialite_sport2_precise1[3] = {
	wxT("100 متر"),
	wxT("200 متر"),
	wxT("400 متر")
};

const wxString specialite_sport2_precise2[3] = {
	wxT("800 متر"),	
	wxT("1500 متر"), 
	wxT("3000 متر")
};

const wxString specialite_sport2_precise3[5] = {
	wxT("5000 متر"),	
	wxT("10000 متر"), 	
	wxT("العدو الريفي"),	
	wxT("نصف الماراثون"),	
	wxT("الماراثون")
};

const wxString specialite_sport2_precise4[4] = {
	wxT("100 متر حواجز"),
	wxT("110 متر حواجز"),
	wxT("400 متر حواجز"),
	wxT("3000 متر موانع")
};

const wxString specialite_sport2_precise5[2] = {
	wxT("100 متر تتابع"),
	wxT("400 متر تتابع")
};


enum { sex_homme=0, sex_femme };
const wxString sex_francais[sex_femme+1] = {
	wxT("ذكر"),
	wxT("أنثى")
};

enum { a_plus=0, a_moin, ab_plus, ab_moin, b_plus, b_moin, o_plus, o_moin };
const wxString groupe_sanguin_francais[o_moin + 1] = {
	wxT("A+"),
	wxT("A-"),
	wxT("AB+"),
	wxT("AB-"),
	wxT("B+"),
	wxT("B-"),
	wxT("O+"),
	wxT("O-")
};

enum { imprimer=0, effacer, enregistrer, ajuster, supprimer, ajouter };
const vector<wxString> list_bas_francais = {
	wxT("طباعة"),
	wxT("مسح"),
	wxT("تسجيل"),
	wxT("تعديل"),
	wxT("حذف"),
	wxT("إضافة البيانة")
};

const vector<short> list_bas_IDs = {
	100,
	101,
	102,
	103,
	104,
	105
};

enum { page_principale_ = 0, suivant_, precedent_, statistique_, listes_, recherche_ };
const vector<wxString> list_haut_francais = {
	wxT("صفحة\nرئيسية"),
	wxT("الرياضي\n التالي"),
	wxT("الرياضي\n سابق"),
	wxT("Statistique"),
	wxT("قائمة\nبيانات"),
	wxT("بحث")
};

const vector<short> list_haut_IDs = {
	106,
	107,
	108,
	109,
	110,
	111
};

const int idd_taille_x = 1100;
const int idd_taille_y = 800;

const short age_min		= 0;
const short age_max		= 120;
const short taille_min	= 100;
const short taille_max	= 250;
const short poid_min	= 40;
const short poid_max	= 300;

const short modifier_photo_id = 112;

#endif