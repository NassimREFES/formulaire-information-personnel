#include "information_personnel.h"

class Liste : public wxFrame
{
public:
	Liste();
	void OnImprimer(wxCommandEvent& event) {}
	void OnPagePrincipale(wxCommandEvent& event) {}
	void OnRecherche(wxCommandEvent& event) {}
	void OnVerif(wxCommandEvent& event) {}
private:
	wxSearchCtrl* recherche_sportif__;
	wxButton* page_principale__;
	wxButton* imprimer;
	wxButton* verif;
	wxListView* mon_tableau;
};

class interface_de_donnee : public wxFrame
{
public :
	friend Liste;
	interface_de_donnee();

	void OnQuit(wxCommandEvent&);
	void OnPaint(wxPaintEvent&);

	void OnAjouter(wxCommandEvent&);
	void OnSupprimer(wxCommandEvent&);
	void OnAjuster(wxCommandEvent&);
	void OnEnregistrer(wxCommandEvent&);
	void OnEffacer(wxCommandEvent&);
	void OnImprimer(wxCommandEvent&);

	void OnPagePrincipale(wxCommandEvent&);
	void OnSuivant(wxCommandEvent&);
	void OnPrecedent(wxCommandEvent&);
	void OnStatistique(wxCommandEvent&);
	void OnListes(wxCommandEvent&);
	void OnRecherche(wxCommandEvent&);

	void OnModifierPhoto(wxCommandEvent&);

	void OnSports(wxCommandEvent&);
	void OnSpecialite(wxCommandEvent&);

	void OnAge(wxSpinEvent&);

	void OnVerifListe(wxCommandEvent&);
	void OnRechercheListe(wxCommandEvent&);
	void OnImprimerListe(wxCommandEvent&);
	void OnPagePrincipaleListe(wxCommandEvent&);
private :
	vector< wxString > donnee_photos;
	vector< vector< wxString > > donnee;
	vector<wxTextCtrl*> tous_donnee;
	vector<wxButton*> list_bas;
	wxChoice* sex_choix;
	wxChoice* groupe_sanguin_choix;
	wxSpinCtrl* age_spin;
	wxSpinCtrl* poid_spin;
	wxSpinCtrl* taille_spin;
	wxMenuBar* menubar;
	wxMenu* fichier;
	wxMenu* action;

	wxToolBar* toolbar;
	wxButton* page_principale;
	wxButton* sportif_suivant;
	wxButton* sportif_precedent;
	int suiveur;
	wxButton* statistique;
	wxButton* liste_sportif;
	wxSearchCtrl* recherche_sportif;

	wxBitmapButton* sb; // photo personnel
	wxButton* modifier_photo;

	wxSpinCtrl* num_dossier_up;
	wxSpinCtrl* num_piece_up;
	wxTextCtrl* annee_entrainement_up;
	wxDatePickerCtrl* date_entrer_up;
	wxDatePickerCtrl* date_sortie_up;

	wxChoice* sport_;
	wxChoice* specialite_;
	wxChoice* specialite_precise;

	wxChoice* situation_familiale;
	wxChoice* wilaya;
	wxSpinCtrl* vue_spin;

	wxChoice* grad_scolair;
	wxTextCtrl* specialite_entraineur;

	vector<wxStaticText*> v;
	vector<wxStaticText*> v6;

	wxDatePickerCtrl* date_naissance_;

	wxFrame* ma_liste;
private :
	void dispertion_des_info();
	void afficher_sportif(int i);
	DECLARE_EVENT_TABLE()
};

pair< vector< vector< wxString > >, vector< wxString > > bd_sportif(const wxString& lien);

BEGIN_EVENT_TABLE(interface_de_donnee, wxFrame)
//EVT_CHOICE(ID_CHOIX, Nouveau::OnChoix)
// list_bas
	EVT_MENU(list_bas_IDs[ajouter], interface_de_donnee::OnAjouter)
	EVT_MENU(list_bas_IDs[supprimer], interface_de_donnee::OnSupprimer)
	EVT_MENU(list_bas_IDs[ajuster], interface_de_donnee::OnAjuster)
	EVT_MENU(list_bas_IDs[enregistrer], interface_de_donnee::OnEnregistrer)
	EVT_MENU(list_bas_IDs[effacer], interface_de_donnee::OnEffacer)
	EVT_MENU(list_bas_IDs[imprimer], interface_de_donnee::OnImprimer)
	EVT_BUTTON(list_bas_IDs[ajouter], interface_de_donnee::OnAjouter)
	EVT_BUTTON(list_bas_IDs[supprimer], interface_de_donnee::OnSupprimer)
	EVT_BUTTON(list_bas_IDs[ajuster], interface_de_donnee::OnAjuster)
	EVT_BUTTON(list_bas_IDs[enregistrer], interface_de_donnee::OnEnregistrer)
	EVT_BUTTON(list_bas_IDs[effacer], interface_de_donnee::OnEffacer)
	EVT_BUTTON(list_bas_IDs[imprimer], interface_de_donnee::OnImprimer)
// list_haut
	EVT_MENU(list_haut_IDs[page_principale_], interface_de_donnee::OnPagePrincipale)
	EVT_MENU(list_haut_IDs[suivant_], interface_de_donnee::OnSuivant)
	EVT_MENU(list_haut_IDs[precedent_], interface_de_donnee::OnPrecedent)
	EVT_MENU(list_haut_IDs[statistique_], interface_de_donnee::OnStatistique)
	EVT_MENU(list_haut_IDs[listes_], interface_de_donnee::OnListes)
	EVT_BUTTON(list_haut_IDs[page_principale_], interface_de_donnee::OnPagePrincipale)
	EVT_BUTTON(list_haut_IDs[suivant_], interface_de_donnee::OnSuivant)
	EVT_BUTTON(list_haut_IDs[precedent_], interface_de_donnee::OnPrecedent)
	EVT_BUTTON(list_haut_IDs[statistique_], interface_de_donnee::OnStatistique)
	EVT_BUTTON(list_haut_IDs[listes_], interface_de_donnee::OnListes)
	EVT_SEARCHCTRL_SEARCH_BTN(list_haut_IDs[recherche_], interface_de_donnee::OnRecherche)

	EVT_BUTTON(modifier_photo_id, interface_de_donnee::OnModifierPhoto)

	EVT_CHOICE(ID_SPORT, interface_de_donnee::OnSports) 
	EVT_CHOICE(ID_SPECIALITE1, interface_de_donnee::OnSpecialite)
	EVT_SPINCTRL(ID_AGE, interface_de_donnee::OnAge)
END_EVENT_TABLE()


interface_de_donnee::interface_de_donnee()
: wxFrame(NULL, wxID_ANY, wxT("إضافة رياضي"), wxDefaultPosition, wxSize(1300, 850)),
	tous_donnee(profession + 1), list_bas(6), suiveur(0), v(16), v6(3)
{
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	wxInitAllImageHandlers();

	for_each(tous_donnee.begin(), tous_donnee.end(), 
		[](wxTextCtrl* a) { a = NULL; });

	menubar = new wxMenuBar;
	menubar->SetBackgroundColour(*wxBLACK);
	fichier = new wxMenu;
	fichier->Append(wxID_ANY, wxT("صفحة رئيسية"));
	fichier->AppendSeparator();
	fichier->Append(wxID_ANY, wxT("الرياضي التالي"));
	fichier->Append(wxID_ANY, wxT("الرياضي سابق"));
	fichier->AppendSeparator();
	fichier->Append(wxID_ANY, list_haut_francais[3]);
	fichier->Append(wxID_ANY, list_haut_francais[4]);
	fichier->AppendSeparator();
	fichier->Append(wxID_EXIT, wxT("خروج"));
	action = new wxMenu;
	action->Append(list_bas_IDs[ajouter], wxT("&Ajouter"));
	action->Append(list_bas_IDs[supprimer], wxT("S&upprimer"));
	action->Append(list_bas_IDs[enregistrer], wxT("&Enregistrer"));
	action->AppendSeparator();
	action->Append(list_bas_IDs[ajuster], wxT("A&juster"));
	action->Append(list_bas_IDs[effacer], wxT("&Effacer"));
	action->AppendSeparator();
	action->Append(list_bas_IDs[imprimer], wxT("&Imprimer"));

	menubar->Append(fichier, wxT("ملف"));
	menubar->Append(action, wxT("عمل"));
	SetMenuBar(menubar);

	dispertion_des_info();

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(interface_de_donnee::OnQuit));
	Connect(wxEVT_PAINT, wxPaintEventHandler(interface_de_donnee::OnPaint));

	//-------------------------------------------------
	pair< vector< vector< wxString > >, vector< wxString > > x = bd_sportif(wxT("tous_donnee.txt"));
	donnee = x.first;
	donnee_photos = x.second;

	afficher_sportif(suiveur);
	SetBackgroundColour(wxColour(56, 56, 56));
}

pair< vector< vector< wxString > >, vector< wxString > > 
	bd_sportif(const wxString& lien)
{
	vector< vector< wxString > > donnee_;
	vector< wxString > donnee_photos_;
	wxFile ifs;
	ifs.Open(lien, wxFile::OpenMode::read);
	wxString* lines = new wxString();
	ifs.ReadAll(lines);
	int count = 1;
	wxArrayString md = wxSplit(*lines, wxChar('|'));
	if (md.size()) {
		md.pop_back();
		vector<wxString> ma_donnee;
		for (int i = 0; i < md.size(); ++i) {
			if (i == 52 * count - 1) {
				donnee_photos_.push_back(md[i]);
				++count;
				donnee_.push_back(ma_donnee);
				ma_donnee.clear();
			}
			else
				ma_donnee.push_back(md[i]);
		}
	}
	return make_pair(donnee_, donnee_photos_);
}

void interface_de_donnee::OnModifierPhoto(wxCommandEvent& event)
{
	wxFileDialog
		ouvrirFileDialog(this, _(""), "", "",
		"photo (*.jpg)|*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (ouvrirFileDialog.ShowModal() == wxID_OK) {
		wxFileInputStream input_stream(ouvrirFileDialog.GetPath());
		if (!input_stream.IsOk()) {
			wxLogError("peux pas ouvrir le fichier '%s'.", ouvrirFileDialog.GetPath());
			return;
		}
		wxBitmap bmp;
		bmp.LoadFile(ouvrirFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);
		sb->SetBitmap(bmp);
		sb->SetLabel(ouvrirFileDialog.GetPath());
	}
}

void interface_de_donnee::OnAge(wxSpinEvent& event)
{
	if (age_spin->GetValue() < 18) {
		situation_familiale->SetSelection(-1);
		situation_familiale->Enable(false);
		v6[adresse + 4]->Enable(false);
		tous_donnee[nom_pere]->Enable(true);
		tous_donnee[telephone_pere]->Enable(true);
		tous_donnee[num_prof]->Enable(true);
		tous_donnee[num_institution]->Enable(true);
		tous_donnee[adresse_institution]->Enable(true);
		tous_donnee[prof_institution]->Enable(true);
		tous_donnee[relation_parent]->Enable(true);
		for (int i = 2; i < 9; ++i)
			v[i]->Enable(true);
	}
	else {
		situation_familiale->SetSelection(0);
		situation_familiale->Enable(true);
		v6[adresse + 4]->Enable(true);
		tous_donnee[nom_pere]->Enable(false);
		tous_donnee[telephone_pere]->Enable(false);
		tous_donnee[num_prof]->Enable(false);
		tous_donnee[num_institution]->Enable(false);
		tous_donnee[adresse_institution]->Enable(false);
		tous_donnee[prof_institution]->Enable(false);
		tous_donnee[relation_parent]->Enable(false);
		for (int i = 2; i < 9; ++i)
			v[i]->Enable(false);
	}
}

wxDateTime str_to_wxDateTime(wxString x)
{
	istringstream iss(x.ToStdString());
	int day, month, year;
	char ch;
	iss >> year >> ch >> month >> ch >> day;
	return wxDateTime(day, (wxDateTime::Month)month, (wxDateTime::Year)year, 0, 0, 0, 0);
}

void interface_de_donnee::afficher_sportif(int j)
{
	if (donnee.size()) {
		for (int i = nom_prenom; i <= profession; ++i) {
			if (tous_donnee[i]) {
				tous_donnee[i]->SetValue(donnee[j][i]);
			}
		}
		if (donnee[j][test_medical][0] == '[')
			donnee[j][test_medical] = donnee[j][test_medical].SubString(1, donnee[j][test_medical].size());
		if (donnee[j][test_medical][donnee[j][test_medical].size() - 1] == ']')
			donnee[j][test_medical] = donnee[j][test_medical].SubString(0, donnee[j][test_medical].size()-2);
		donnee[j][test_medical].Replace(',', '\n');
		tous_donnee[test_medical]->SetValue(donnee[j][test_medical]);
		if (donnee[j][blessur_precedent][0] == '[')
			donnee[j][blessur_precedent] = donnee[j][blessur_precedent].SubString(1, donnee[j][blessur_precedent].size());
		if (donnee[j][blessur_precedent][donnee[j][blessur_precedent].size() - 1] == ']')
			donnee[j][blessur_precedent] = donnee[j][blessur_precedent].SubString(0, donnee[j][blessur_precedent].size() - 2);
		donnee[j][blessur_precedent].Replace(',', '\n');
		tous_donnee[blessur_precedent]->SetValue(donnee[j][blessur_precedent]);
	
		long val;
		donnee[j][sex].ToLong(&val, 10);
		sex_choix->SetSelection(val);

		age_spin->SetValue(donnee[j][age]);
		OnAge(wxSpinEvent());
		poid_spin->SetValue(donnee[j][poid]);
		taille_spin->SetValue(donnee[j][taille]);
		donnee[j][groupe_sanguin].ToLong(&val, 10);
		groupe_sanguin_choix->SetSelection(val);

		donnee[j][donnee[j].size() - 14].ToLong(&val, 10);
		num_dossier_up->SetValue(val);
		donnee[j][donnee[j].size() - 13].ToLong(&val, 10);
		num_piece_up->SetValue(val);
		annee_entrainement_up->SetValue(donnee[j][donnee[j].size() - 12]);
		date_entrer_up->SetValue(str_to_wxDateTime(donnee[j][donnee[j].size() - 11]));
		date_sortie_up->SetValue(str_to_wxDateTime(donnee[j][donnee[j].size() - 10]));
		donnee[j][donnee[j].size() - 9].ToLong(&val, 10);
		sport_->SetSelection(val);
		OnSports(wxCommandEvent());
		donnee[j][donnee[j].size() - 8].ToLong(&val, 10);
		specialite_->SetSelection(val);
		OnSpecialite(wxCommandEvent());
		donnee[j][donnee[j].size() - 7].ToLong(&val, 10);
		specialite_precise->SetSelection(val);
		donnee[j][donnee[j].size() - 6].ToLong(&val, 10);
		situation_familiale->SetSelection(val);
		donnee[j][donnee[j].size() - 5].ToLong(&val, 10);
		wilaya->SetSelection(val);
		donnee[j][donnee[j].size() - 4].ToLong(&val, 10);
		vue_spin->SetValue(val);
		donnee[j][donnee[j].size() - 3].ToLong(&val, 10);
		grad_scolair->SetSelection(val);
		specialite_entraineur->SetValue(donnee[j][donnee[j].size() - 2]);
		date_naissance_->SetValue(str_to_wxDateTime(donnee[j][donnee[j].size() - 1]));
		wxBitmap bmp;
		bmp.LoadFile(donnee_photos[j], wxBITMAP_TYPE_JPEG);
		sb->SetBitmap(bmp);
	}
}

void interface_de_donnee::OnQuit(wxCommandEvent& event)
{
	Close(true);
}

void interface_de_donnee::OnPaint(wxPaintEvent& event)
{
	/*wxBufferedPaintDC dc(this);
	PrepareDC(dc);
	wxBitmap bmp("sport1.jpg", wxBITMAP_TYPE_JPEG);
	dc.DrawBitmap(bmp, wxPoint(0, 0));*/
}

void interface_de_donnee::OnAjouter(wxCommandEvent& event)
{
	vector<wxString> nouveau_donnee(profession + 15);
	for (int i = nom_prenom; i <= profession; ++i) {
		if (tous_donnee[i]) {
			if (tous_donnee[i]->IsEmpty())
				nouveau_donnee[i] = wxT("?");
			else
				nouveau_donnee[i] = tous_donnee[i]->GetValue();
		}
	}

	nouveau_donnee[sex] = wxString::Format(wxT("%d"), sex_choix->GetSelection());
	nouveau_donnee[age] = wxString::Format(wxT("%d"), age_spin->GetValue());
	nouveau_donnee[poid] = wxString::Format(wxT("%d"), poid_spin->GetValue());
	nouveau_donnee[taille] = wxString::Format(wxT("%d"), taille_spin->GetValue());
	nouveau_donnee[groupe_sanguin] = wxString::Format(wxT("%d"), groupe_sanguin_choix->GetSelection());
	//-----------------------------------
	nouveau_donnee[nouveau_donnee.size()-14] = (wxString::Format(wxT("%d"), num_dossier_up->GetValue()));
	nouveau_donnee[nouveau_donnee.size()-13] = wxString::Format(wxT("%d"), num_piece_up->GetValue());
	nouveau_donnee[nouveau_donnee.size()-12] = wxString::Format(wxT("%s"), annee_entrainement_up->GetValue());
	nouveau_donnee[nouveau_donnee.size() - 11] = date_entrer_up->GetValue().FormatISODate();
	nouveau_donnee[nouveau_donnee.size() - 10] = date_sortie_up->GetValue().FormatISODate();
	nouveau_donnee[nouveau_donnee.size()-9] = wxString::Format(wxT("%d"), sport_->GetSelection());
	nouveau_donnee[nouveau_donnee.size()-8] = wxString::Format(wxT("%d"), specialite_->GetSelection());
	nouveau_donnee[nouveau_donnee.size()-7] = wxString::Format(wxT("%d"), specialite_precise->GetSelection());
	nouveau_donnee[nouveau_donnee.size()-6] = wxString::Format(wxT("%d"), situation_familiale->GetSelection());
	nouveau_donnee[nouveau_donnee.size()-5] = wxString::Format(wxT("%d"), wilaya->GetSelection());
	nouveau_donnee[nouveau_donnee.size()-4] = wxString::Format(wxT("%d"), vue_spin->GetValue());
	nouveau_donnee[nouveau_donnee.size()-3] = wxString::Format(wxT("%d"), grad_scolair->GetSelection());
	nouveau_donnee[nouveau_donnee.size()-2] = wxString::Format(wxT("%s"), specialite_entraineur->GetValue());
	nouveau_donnee[nouveau_donnee.size() - 1] = date_naissance_->GetValue().FormatISODate();

	donnee.push_back(nouveau_donnee);
	donnee_photos.push_back(sb->GetLabel());

	wxMessageBox(wxT("Ajou de donnée effectuer"), wxT("Information"));
}

void interface_de_donnee::OnSupprimer(wxCommandEvent& event)
{
	if (donnee.size()) {
		vector< vector< wxString > > nouveau_donnee;
		vector< wxString> nouveau_donnee_photos;
		for (int i = 0; i < donnee.size(); ++i) {
			if (i != suiveur) {
				nouveau_donnee.push_back(donnee[i]);
				nouveau_donnee_photos.push_back(donnee_photos[i]);
			}
		}
		donnee = nouveau_donnee;
		donnee_photos = nouveau_donnee_photos;
		suiveur = 0;
		if (donnee.size()) {
			afficher_sportif(suiveur);
			wxMessageBox(wxT("Suppression effectuer"), wxT("Information"));
		}
		else
			OnEffacer(event);
	}
}

void interface_de_donnee::OnAjuster(wxCommandEvent& event)
{
	if (donnee.size()) {
		for (int i = nom_prenom; i <= profession; ++i) {
			if (tous_donnee[i]) {
				if (tous_donnee[i]->IsEmpty())
					donnee[suiveur][i] = wxT("?");
				else
					donnee[suiveur][i] = tous_donnee[i]->GetValue();
			}
		}

		donnee[suiveur][sex] = wxString::Format(wxT("%d"), sex_choix->GetSelection());
		donnee[suiveur][age] = wxString::Format(wxT("%d"), age_spin->GetValue());
		donnee[suiveur][poid] = wxString::Format(wxT("%d"), poid_spin->GetValue());
		donnee[suiveur][taille] = wxString::Format(wxT("%d"), taille_spin->GetValue());
		donnee[suiveur][groupe_sanguin] = wxString::Format(wxT("%d"), groupe_sanguin_choix->GetSelection());

		donnee[suiveur][donnee[suiveur].size() - 14] = (wxString::Format(wxT("%d"), num_dossier_up->GetValue()));
		donnee[suiveur][donnee[suiveur].size() - 13] = wxString::Format(wxT("%d"), num_piece_up->GetValue());
		donnee[suiveur][donnee[suiveur].size() - 12] = wxString::Format(wxT("%s"), annee_entrainement_up->GetValue());
		donnee[suiveur][donnee[suiveur].size() - 11] = date_entrer_up->GetValue().FormatISODate();
		donnee[suiveur][donnee[suiveur].size() - 10] = date_sortie_up->GetValue().FormatISODate();
		donnee[suiveur][donnee[suiveur].size() - 9] = wxString::Format(wxT("%d"), sport_->GetSelection());
		donnee[suiveur][donnee[suiveur].size() - 8] = wxString::Format(wxT("%d"), specialite_->GetSelection());
		donnee[suiveur][donnee[suiveur].size() - 7] = wxString::Format(wxT("%d"), specialite_precise->GetSelection());
		donnee[suiveur][donnee[suiveur].size() - 6] = wxString::Format(wxT("%d"), situation_familiale->GetSelection());
		donnee[suiveur][donnee[suiveur].size() - 5] = wxString::Format(wxT("%d"), wilaya->GetSelection());
		donnee[suiveur][donnee[suiveur].size() - 4] = wxString::Format(wxT("%d"), vue_spin->GetValue());
		donnee[suiveur][donnee[suiveur].size() - 3] = wxString::Format(wxT("%d"), grad_scolair->GetSelection());
		donnee[suiveur][donnee[suiveur].size() - 2] = wxString::Format(wxT("%s"), specialite_entraineur->GetValue());
		donnee[suiveur][donnee[suiveur].size() - 1] = date_naissance_->GetValue().FormatISODate();

		donnee_photos[suiveur] = sb->GetLabel();

		wxMessageBox(wxT("Ajustation effectuer"), wxT("Information"));
	}
}

void interface_de_donnee::OnEnregistrer(wxCommandEvent& event)
{
	wxFile ofs;
	ofs.Open(wxT("tous_donnee.txt"), wxFile::OpenMode::write);
	for (int j = 0; j < donnee.size(); ++j) {
		for (int i = 0; i < donnee[j].size(); ++i) {
			if (donnee[j][i] == wxEmptyString)
					ofs.Write(wxString("?|"));
				else if (i == test_medical || i == blessur_precedent) {
					ofs.Write(wxString("["));
					donnee[j][i].Replace("\n", ",");
					cout << donnee[j][i];
					ofs.Write(donnee[j][i]);
					ofs.Write(wxString("]"));
					ofs.Write(wxString(wxT("|")));
				}
				else {
					ofs.Write(donnee[j][i]);
					ofs.Write(wxString("|"));
				}
		}

		ofs.Write(donnee_photos[j]);
		ofs.Write(wxString("|"));
	}
	ofs.Close();

	wxMessageBox(wxT("Enregistrement effectuer"), wxT("Information"));
}

void interface_de_donnee::OnEffacer(wxCommandEvent& event)
{
	for_each(tous_donnee.begin(), tous_donnee.end(),
		[](wxTextCtrl* a) { if (a) { a->SetValue(""); } } );
	num_dossier_up->SetValue("1");
	num_piece_up->SetValue("1");
	annee_entrainement_up->SetValue("2.../2...");
	//--------------------------------
	sex_choix->SetSelection(sex_homme);
	age_spin->SetValue(langue_francais[age]);
	poid_spin->SetValue(langue_francais[poid]);
	taille_spin->SetValue(langue_francais[taille]);
	groupe_sanguin_choix->SetSelection(a_plus);
	//--------------------------------
	sport_->SetSelection(0);
	situation_familiale->SetSelection(0);
	wilaya->SetSelection(0);
	vue_spin->SetValue(8);
	grad_scolair->SetSelection(0);
	specialite_entraineur->SetValue(wxEmptyString);

	wxMessageBox(wxT("Effacer effectuer"), wxT("Information"));
}

void interface_de_donnee::OnImprimer(wxCommandEvent& event)
{

}

void interface_de_donnee::OnPagePrincipale(wxCommandEvent& event)
{

}

void interface_de_donnee::OnSuivant(wxCommandEvent& event)
{
	if (suiveur < donnee.size() - 1) {
		++suiveur;
		afficher_sportif(suiveur);
	}
}

void interface_de_donnee::OnPrecedent(wxCommandEvent& event)
{
	if (0 < suiveur) {
		--suiveur;
		afficher_sportif(suiveur);
	}
}

void interface_de_donnee::OnStatistique(wxCommandEvent& event)
{

}

void interface_de_donnee::OnVerifListe(wxCommandEvent& event) 
{

}

void interface_de_donnee::OnRechercheListe(wxCommandEvent& event)
{

}

void interface_de_donnee::OnImprimerListe(wxCommandEvent& event)
{

}

void interface_de_donnee::OnPagePrincipaleListe(wxCommandEvent& event)
{

}

void interface_de_donnee::OnListes(wxCommandEvent& event)
{
	pair< vector< vector< wxString > >, vector< wxString > > x = bd_sportif(wxT("tous_donnee.txt"));
	ma_liste = new wxFrame(this, wxID_ANY, wxT("قائمة بيانات"), wxDefaultPosition, wxSize(1050, 400));
	//------------------------------------------------
	wxSearchCtrl* recherche_sportif__ = new wxSearchCtrl(ma_liste, ID_RCH, list_haut_francais[recherche_]);
	recherche_sportif__->SetDescriptiveText(list_haut_francais[recherche_]);
	wxButton* page_principale__ = new wxButton(ma_liste, ID_PGP, list_haut_francais[page_principale_]);
	page_principale__->SetBitmap(wxBitmap(wxT("page_principale.png"), wxBITMAP_TYPE_PNG));
	wxButton* imprimer = new wxButton(ma_liste, ID_IMPR, list_bas_francais[0]);
	imprimer->SetBitmap(wxBitmap(wxT("imprimer.png"), wxBITMAP_TYPE_PNG));
	wxButton* verif = new wxButton(ma_liste, ID_VERIF, wxT("جدول مراقبة\nالأداء"));
	verif->SetBitmap(wxBitmap(wxT("statistique.png"), wxBITMAP_TYPE_PNG));
	wxListView* mon_tableau = new wxListView(ma_liste, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	//-------------------------------------------------
	ma_liste->Connect(ID_RCH, wxEVT_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler(interface_de_donnee::OnRechercheListe));
	ma_liste->Connect(ID_PGP, wxEVT_BUTTON, wxCommandEventHandler(interface_de_donnee::OnPagePrincipaleListe));
	ma_liste->Connect(ID_IMPR, wxEVT_BUTTON, wxCommandEventHandler(interface_de_donnee::OnImprimerListe));
	ma_liste->Connect(ID_VERIF, wxEVT_BUTTON, wxCommandEventHandler(interface_de_donnee::OnVerifListe));
	//-------------------------------------------------
	vector<wxListItem> l(10);
	for (int i = 0; i < l.size(); ++i) {
		l[i].SetId(i);
		l[i].SetWidth(100);
	}
	l[0].SetWidth(150);
	l[0].SetText(wxT("إختصاص"));
	l[1].SetText(wxT("الفئة العمرية"));
	l[2].SetText(wxT("الدم"));
	l[3].SetText(wxT("Kg"));
	l[4].SetText(wxT("CM"));
	l[5].SetText(langue_francais[1]);
	l[6].SetText(wxT("تاريخ الإزدياد"));
	l[7].SetText(langue_francais[0]);
	l[8].SetText(kk[1]);
	l[9].SetText(kk[0]);
	for (int i = 0; i < l.size(); ++i) 
		mon_tableau->InsertColumn(i, l[i]);
	
	for (int i = 0; i < x.first.size(); ++i) {
		long val = 0;
		mon_tableau->InsertItem(i, wxT(""));
		mon_tableau->SetItem(i, 9, x.first[i][x.first[i].size() - 14]);
		mon_tableau->SetItem(i, 8, x.first[i][x.first[i].size() - 13]);
		mon_tableau->SetItem(i, 7, x.first[i][nom_prenom]);
		mon_tableau->SetItem(i, 6, x.first[i][x.first[i].size() - 1]);
		mon_tableau->SetItem(i, 5, x.first[i][date_naissance]);
		mon_tableau->SetItem(i, 4, x.first[i][taille]);
		mon_tableau->SetItem(i, 3, x.first[i][poid]);
		x.first[i][groupe_sanguin].ToLong(&val, 10);
		mon_tableau->SetItem(i, 2, groupe_sanguin_choix->GetString(val));
		mon_tableau->SetItem(i, 1, x.first[i][face_specialite]);
		x.first[i][x.first[i].size() - 8].ToLong(&val, 10);
		if (val == -1) {
			mon_tableau->SetItem(i, 0, x.first[i][x.first[i].size() - 2]);
		}
		else {
			int v = sport_->GetSelection();
			long vv;
			x.first[i][x.first[i].size() - 9].ToLong(&vv, 10);
			sport_->SetSelection(vv);
			OnSports(event);
			mon_tableau->SetItem(i, 0, specialite_->GetString(val));
			sport_->SetSelection(v);
			OnSports(event);
		}
		if (i % 2) {
			mon_tableau->SetItemBackgroundColour(l[i], wxColour(56, 56, 56));
			mon_tableau->SetItemTextColour(l[i], *wxRED);
		}
		else {
			//mon_tableau->SetItemBackgroundColour(l[i], *wxCYAN);
			//mon_tableau->SetItemTextColour(l[i], *wxRED);
		}
	}

	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	hbox2->Add(verif, 0, wxALL, 2);
	hbox2->Add(imprimer, 0, wxALL, 2);
	hbox2->Add(page_principale__, 0, wxALL, 2);
	hbox3->Add(recherche_sportif__, 0, wxALL, 2);
	hbox->Add(hbox3, 4, wxALIGN_LEFT | wxALL, 2);
	hbox->Add(hbox2, 1, wxALIGN_RIGHT | wxALL | wxEXPAND, 2);
	vbox->Add(hbox, 0, wxALL | wxEXPAND, 2);
	vbox->Add(mon_tableau, 1, wxEXPAND | wxALL, 2);
	ma_liste->SetSizer(vbox);
	ma_liste->SetBackgroundColour(wxColour(56, 56, 56));
	ma_liste->Show(true);
}

void interface_de_donnee::OnRecherche(wxCommandEvent& event)
{

}

void interface_de_donnee::OnSpecialite(wxCommandEvent& event)
{
	int ii = specialite_->GetSelection();
	specialite_precise->Enable(true);
	v[13]->Enable(true);
	if (sport_->GetSelection() < 1) {
		specialite_entraineur->Enable(false);
		v[16]->Enable(false);
		specialite_entraineur->SetValue(wxT(""));
	}
	for (int i = 0; i < 5; ++i)
		specialite_precise->SetString(i, wxEmptyString);
	if (!sport_->GetSelection()) {
		specialite_precise->Enable(false);
		v[13]->Enable(false);
		specialite_precise->SetSelection(-1);
	}
	else {
		switch (ii) {
		case 0:
			for (int i = 0; i < 3; ++i)
				specialite_precise->SetString(i, specialite_sport2_precise1[i]);
			break;
		case 1:
			for (int i = 0; i < 3; ++i)
				specialite_precise->SetString(i, specialite_sport2_precise2[i]);
			break;
		case 2:
			for (int i = 0; i < 5; ++i)
				specialite_precise->SetString(i, specialite_sport2_precise3[i]);
			break;
		case 3:
			for (int i = 0; i < 4; ++i)
				specialite_precise->SetString(i, specialite_sport2_precise4[i]);
			break;
		case 4:
			for (int i = 0; i < 2; ++i)
				specialite_precise->SetString(i, specialite_sport2_precise5[i]);
			break;
		case 5: case 6: case 7: case 8:
			specialite_precise->Enable(false);
			v[13]->Enable(false);
			specialite_precise->SetSelection(-1);
			break;
		default: 
			specialite_precise->Enable(false);
			v[13]->Enable(false); 
			specialite_precise->SetSelection(-1);
			break;
		}
	}
}

void interface_de_donnee::OnSports(wxCommandEvent& event)
{
	int i = sport_->GetSelection();
	
	if (i > 1) {
		specialite_->Enable(false);
		v[12]->Enable(false);
		specialite_->SetSelection(-1);
		specialite_precise->Enable(false);
		v[13]->Enable(false);
		specialite_precise->SetSelection(-1);
		specialite_entraineur->Enable(true);
		v[16]->Enable(true);
	}
	else {
		specialite_->Enable(true);
		v[12]->Enable(true);
		specialite_precise->Enable(true);
		v[13]->Enable(true);
		specialite_entraineur->Enable(false);
		v[16]->Enable(false);
		specialite_entraineur->SetValue(wxT(""));
		switch (i) {
		case 0 :
			v[13]->Enable(false);
			specialite_precise->Enable(false);
			specialite_precise->SetSelection(-1);
			for (int i = 0; i < 12; ++i) 
				specialite_->SetString(i, specialite_sport1[i]);
			specialite_->SetSelection(0);
			break;
		case 1 :
			specialite_precise->Enable(true);
			v[13]->Enable(true);
			specialite_->SetString(9, wxEmptyString);
			specialite_->SetString(10, wxEmptyString);
			specialite_->SetString(11, wxEmptyString);
			specialite_->SetColumns(9);
			for (int i = 0; i < 9; ++i)
				specialite_->SetString(i, specialite_sport2[i]);
			//specialite_->SetSelection(0);
			break;
		default :
			break;
		}
	}
}

void interface_de_donnee::dispertion_des_info()
{
	wxBoxSizer* global_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* global_mid_sizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer* hs0 = new wxStaticBoxSizer(wxHORIZONTAL, this);
	page_principale = new wxButton(this, list_haut_IDs[page_principale_], list_haut_francais[page_principale_]);
	page_principale->SetBitmap(wxBitmap(wxT("page_principale.png"), wxBITMAP_TYPE_PNG));
	//statistique = new wxButton(this, list_haut_IDs[statistique_], list_haut_francais[statistique_]);
	//statistique->SetBitmap(wxBitmap(wxT("statistique.png"), wxBITMAP_TYPE_PNG));
	liste_sportif = new wxButton(this, list_haut_IDs[listes_], list_haut_francais[listes_]);
	liste_sportif->SetBitmap(wxBitmap(wxT("liste.png"), wxBITMAP_TYPE_PNG));

	recherche_sportif = new wxSearchCtrl(this, list_haut_IDs[recherche_], list_haut_francais[recherche_]);
	recherche_sportif->SetDescriptiveText(list_haut_francais[recherche_]);
	wxMenu* a = new wxMenu;
	/*a->Append(wxID_ANY, wxT("loool 1"));
	a->Append(wxID_ANY, wxT("loool 2"));
	a->Append(wxID_ANY, wxT("loool 3"));
	recherche_sportif->SetMenu(a);
	recherche_sportif->SetDescriptiveText(wxT("looool1"));*/
	wxBoxSizer* dd = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* dd2 = new wxBoxSizer(wxHORIZONTAL);
	dd->Add(recherche_sportif, 0, wxALL, 2);
	dd2->Add(liste_sportif, 0, wxALL, 2);
	dd2->Add(page_principale, 0, wxALL, 2);
	hs0->Add(dd, 4, wxALIGN_LEFT | wxALL, 2);
	hs0->Add(dd2, 1, wxALIGN_RIGHT | wxALL | wxEXPAND, 2);
	//hs0->Add(recherche_sportif, 0, wxALL | wxALIGN_RIGHT, 5);
	//hs0->Add(statistique, 0, wxALL, 5);
	//hs0->Add(liste_sportif, 0, wxALL | wxALIGN_RIGHT, 5);
	//hs0->Add(page_principale, 0, wxALL | wxALIGN_RIGHT, 5);
	
	//-----------------------------
	wxStaticBoxSizer* hs1 = new wxStaticBoxSizer(wxHORIZONTAL, this);
	wxFlexGridSizer* haut_sizer = new wxFlexGridSizer(2, 5, 5, 5);
	wxStaticText* nd = new wxStaticText(hs1->GetStaticBox(), ID_kk[0], kk[0]);
	wxStaticText* nd2 = new wxStaticText(hs1->GetStaticBox(), ID_kk[1], kk[1]);
	wxStaticText* nd3 = new wxStaticText(hs1->GetStaticBox(), ID_kk[2], kk[2]);
	wxStaticText* nd4 = new wxStaticText(hs1->GetStaticBox(), ID_kk[3], kk[3]);
	wxStaticText* nd5 = new wxStaticText(hs1->GetStaticBox(), ID_kk[4], kk[4]);
	nd->SetForegroundColour(*wxRED);
	nd2->SetForegroundColour(*wxRED);
	nd3->SetForegroundColour(*wxRED);
	nd4->SetForegroundColour(*wxRED);
	nd5->SetForegroundColour(*wxRED);
	num_dossier_up = new wxSpinCtrl(hs1->GetStaticBox(), ID_kk[0], wxT("1"),
		wxDefaultPosition, wxDefaultSize, 16896L, 0, numeric_limits<int>::max());
	num_piece_up = new wxSpinCtrl(hs1->GetStaticBox(), ID_kk[1], wxT("1"),
		wxDefaultPosition, wxDefaultSize, 16896L, 0, numeric_limits<int>::max());
	annee_entrainement_up = new wxTextCtrl(hs1->GetStaticBox(), ID_kk[2], wxT("2.../2..."), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	date_entrer_up = new wxDatePickerCtrl(hs1->GetStaticBox(), ID_kk[3]);
	date_sortie_up = new wxDatePickerCtrl(hs1->GetStaticBox(), ID_kk[4]);
	haut_sizer->Add(nd5, 0, wxALIGN_RIGHT);
	haut_sizer->Add(nd4, 0, wxALIGN_RIGHT);
	haut_sizer->Add(nd3, 0, wxALIGN_RIGHT);
	haut_sizer->Add(nd2, 0, wxALIGN_RIGHT);
	haut_sizer->Add(nd, 0, wxALIGN_RIGHT);
	haut_sizer->Add(date_sortie_up);
	haut_sizer->Add(date_entrer_up);
	haut_sizer->Add(annee_entrainement_up);
	haut_sizer->Add(num_piece_up);
	haut_sizer->Add(num_dossier_up);
	hs1->Add(haut_sizer);
	//-------------------------------
	wxStaticBoxSizer* hs2 = new wxStaticBoxSizer(wxVERTICAL, this);
	wxStaticBoxSizer* hs22 = new wxStaticBoxSizer(wxHORIZONTAL, hs2->GetStaticBox());
	wxFlexGridSizer* gauche_up_sizer = new wxFlexGridSizer(6, 2, 5, 5);
	gauche_up_sizer->AddGrowableCol(0, 1);
	gauche_up_sizer->AddGrowableCol(1, 1);
	for (int i = 1; i < 11; ++i) {
		if (i < 9) {
			tous_donnee[grade_scolair_sportif + i] = new wxTextCtrl(hs2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
				wxDefaultSize, wxTE_RIGHT);
			tous_donnee[grade_scolair_sportif + i]->SetHint(langue_francais[grade_scolair_sportif + i]);
		}
		else
		{
			tous_donnee[grade_scolair_sportif + i] = new wxTextCtrl(hs22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
				wxDefaultSize, wxTE_RIGHT);
			tous_donnee[grade_scolair_sportif + i]->SetHint(langue_francais[grade_scolair_sportif + i]);
		}
	}
	//vector<wxStaticText*> v(16);
	for (int i = 0; i < 16; ++i) {
		if (i < 9) {
			v[i] = new wxStaticText(hs2->GetStaticBox(), wxID_ANY, langue_francais[grade_scolair_sportif + i]);
			v[i]->SetForegroundColour(*wxRED);
		}
		else {
			v[i] = new wxStaticText(hs22->GetStaticBox(), wxID_ANY, langue_francais[grade_scolair_sportif + i]);
			v[i]->SetForegroundColour(*wxRED);
		}
	}
	grad_scolair = new wxChoice(hs2->GetStaticBox(), ID_GRAD_SCOLAIR, wxDefaultPosition, wxDefaultSize, 6, grad_scolair_list);
	gauche_up_sizer->Add(v[1], 0, wxALIGN_RIGHT, 2);
	gauche_up_sizer->Add(v[0], 0, wxALIGN_RIGHT, 2);
	gauche_up_sizer->Add(tous_donnee[grade_scolair_sportif + 1], 1, wxEXPAND | wxALL, 2);
	gauche_up_sizer->Add(grad_scolair, 1, wxEXPAND | wxALL, 2);
	gauche_up_sizer->Add(v[3], 0, wxALIGN_RIGHT, 2);
	gauche_up_sizer->Add(v[2], 0, wxALIGN_RIGHT, 2);
	gauche_up_sizer->Add(tous_donnee[grade_scolair_sportif + 3], 1, wxEXPAND | wxALL, 2);
	gauche_up_sizer->Add(tous_donnee[grade_scolair_sportif + 2], 1, wxEXPAND | wxALL, 2);
	gauche_up_sizer->Add(v[5], 0, wxALIGN_RIGHT, 2);
	gauche_up_sizer->Add(v[4], 0, wxALIGN_RIGHT, 2);
	gauche_up_sizer->Add(tous_donnee[grade_scolair_sportif + 5], 1, wxEXPAND | wxALL, 2);
	gauche_up_sizer->Add(tous_donnee[grade_scolair_sportif + 4], 1, wxEXPAND | wxALL, 2);
	hs2->Add(gauche_up_sizer, 0, wxEXPAND | wxALL, 2);
	wxFlexGridSizer* gauche_mid_sizer = new wxFlexGridSizer(2, 3, 2, 2);
	gauche_mid_sizer->AddGrowableCol(0, 1);
	gauche_mid_sizer->AddGrowableCol(1, 1);
	gauche_mid_sizer->AddGrowableCol(2, 1);
	gauche_mid_sizer->Add(v[8], 0, wxALIGN_RIGHT, 2);
	gauche_mid_sizer->Add(v[7], 0, wxALIGN_RIGHT, 2);
	gauche_mid_sizer->Add(v[6], 0, wxALIGN_RIGHT, 2);
	gauche_mid_sizer->Add(tous_donnee[grade_scolair_sportif + 8], 1, wxEXPAND | wxALL, 2);
	gauche_mid_sizer->Add(tous_donnee[grade_scolair_sportif + 7], 1, wxEXPAND | wxALL, 2);
	gauche_mid_sizer->Add(tous_donnee[grade_scolair_sportif + 6], 1, wxEXPAND | wxALL, 2);
	hs2->Add(gauche_mid_sizer, 0, wxEXPAND | wxALL, 2);
	wxFlexGridSizer* gauche_down_sizer = new wxFlexGridSizer(8, 2, 2, 2);
	gauche_down_sizer->AddGrowableCol(0, 1);
	gauche_down_sizer->AddGrowableCol(1, 1);
	gauche_down_sizer->AddGrowableRow(7);
	gauche_down_sizer->Add(v[10], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(v[9], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(tous_donnee[grade_scolair_sportif + 10], 1, wxEXPAND | wxALL, 2);
	gauche_down_sizer->Add(tous_donnee[grade_scolair_sportif + 9], 1, wxEXPAND | wxALL, 2);
	sport_ = new wxChoice(hs22->GetStaticBox(), ID_SPORT, wxDefaultPosition, wxDefaultSize, 9, sports);
	wxArrayString aA(12, wxEmptyString);
	wxArrayString aAA(5, wxEmptyString);
	specialite_ = new wxChoice(hs22->GetStaticBox(), ID_SPECIALITE1, wxDefaultPosition, wxDefaultSize, aA);
	specialite_precise = new wxChoice(hs22->GetStaticBox(), ID_SPECIALITE1_PRECISE, wxDefaultPosition, wxDefaultSize, aAA);
	tous_donnee[face_specialite] = new wxTextCtrl(hs22->GetStaticBox(), ID_FACE_SPECIALITE, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	tous_donnee[blessur_precedent] = new wxTextCtrl(hs22->GetStaticBox(), ID_FACE_SPECIALITE, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT|wxTE_MULTILINE);
	tous_donnee[face_specialite]->SetHint(wxT("الفئة العمرية"));
	specialite_entraineur = new wxTextCtrl(hs22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	specialite_entraineur->Enable(false);
	v.push_back(new wxStaticText(hs22->GetStaticBox(), ID_SPECIALITE_ENTRAINEUR, wxT("إختصاص")));
	v[v.size()-1]->SetForegroundColour(*wxRED);
	v[v.size() - 1]->Enable(false);
	//tous_donnee[blessur_precedent]->SetHint(wxT("إصابات السابقة"));
	gauche_down_sizer->Add(v[12], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(v[11], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(specialite_, 1, wxEXPAND | wxALL, 2);
	gauche_down_sizer->Add(sport_, 1, wxEXPAND | wxALL, 2);
	gauche_down_sizer->Add(v[14], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(v[13], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(tous_donnee[face_specialite], 1, wxEXPAND | wxALL, 2);
	gauche_down_sizer->Add(specialite_precise, 1, wxEXPAND | wxALL | wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(v[15], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(v[16], 0, wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(tous_donnee[blessur_precedent], 1, wxEXPAND | wxALL | wxALIGN_RIGHT, 2);
	gauche_down_sizer->Add(specialite_entraineur, 1, wxEXPAND | wxALL | wxALIGN_RIGHT, 2);
	hs22->Add(gauche_down_sizer, 1, wxEXPAND | wxALL | wxALIGN_RIGHT, 2);
	hs2->Add(hs22, 1, wxEXPAND | wxALL, 2);
	//-------------------------------
	wxStaticBoxSizer* hs3 = new wxStaticBoxSizer(wxHORIZONTAL, this);
	for (int i = 0; i < list_bas.size(); ++i) {
		list_bas[i] = new wxButton(hs3->GetStaticBox(), list_bas_IDs[i], list_bas_francais[i]);
		list_bas[i]->SetForegroundColour(*wxRED);
		//list_bas[i]->SetBackgroundColour(*wxBLACK);
	}

	sportif_suivant = new wxButton(hs3->GetStaticBox(), list_haut_IDs[suivant_], list_haut_francais[suivant_]);
	sportif_suivant->SetBitmap(wxBitmap(wxT("suivant.png"), wxBITMAP_TYPE_PNG));
	sportif_suivant->SetForegroundColour(*wxRED);
	//sportif_suivant->SetBackgroundColour(*wxBLACK);
	sportif_precedent = new wxButton(hs3->GetStaticBox(), list_haut_IDs[precedent_], list_haut_francais[precedent_]);
	sportif_precedent->SetBitmap(wxBitmap(wxT("precedent.png"), wxBITMAP_TYPE_PNG));
	sportif_precedent->SetForegroundColour(*wxRED);
	//sportif_precedent->SetBackgroundColour(*wxBLACK);
	
	list_bas[imprimer]->SetBitmap(wxBitmap(wxT("imprimer.png"), wxBITMAP_TYPE_PNG));
	list_bas[effacer]->SetBitmap(wxBitmap(wxT("effacer.png"), wxBITMAP_TYPE_PNG));
	list_bas[ajuster]->SetBitmap(wxBitmap(wxT("ajuster.png"), wxBITMAP_TYPE_PNG));
	list_bas[enregistrer]->SetBitmap(wxBitmap(wxT("enregistrer.png"), wxBITMAP_TYPE_PNG));
	list_bas[ajouter]->SetBitmap(wxBitmap(wxT("ajouter.png"), wxBITMAP_TYPE_PNG));
	list_bas[supprimer]->SetBitmap(wxBitmap(wxT("supprimer.png"), wxBITMAP_TYPE_PNG));
	hs3->Add(list_bas[imprimer], 0, wxALL, 2);
	hs3->Add(list_bas[enregistrer], 0, wxALL, 2);
	hs3->Add(list_bas[ajuster], 0, wxALL, 2);
	hs3->Add(list_bas[effacer], 0, wxALL, 2);
	hs3->Add(list_bas[supprimer], 0, wxALL, 2);
	hs3->Add(list_bas[ajouter], 0, wxALL, 2);
	hs3->Add(sportif_suivant, 0, wxALL, 2);
	hs3->Add(sportif_precedent, 0, wxALL, 2);
	
	//-------------------------------
	wxStaticBoxSizer* hs4g = new wxStaticBoxSizer(wxVERTICAL, this);
	wxStaticBoxSizer* hs4 = new wxStaticBoxSizer(wxHORIZONTAL, hs4g->GetStaticBox());
	wxBoxSizer* hss41 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hss42 = new wxBoxSizer(wxVERTICAL);

	//vector<wxStaticText*> v6(3);
	for (int i = 0; i < 3; ++i) {
		v6[i] = new wxStaticText(hs4->GetStaticBox(), wxID_ANY, langue_francais[nom_prenom + i]);
		tous_donnee[i] = new wxTextCtrl(hs4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
			wxDefaultSize, wxTE_RIGHT);
		tous_donnee[i]->SetHint(langue_francais[i]);
		v6[i]->SetForegroundColour(*wxRED);
	}
	wxFlexGridSizer* lol = new wxFlexGridSizer(2, 2, 2, 2);
	lol->AddGrowableCol(0, 1);
	lol->AddGrowableCol(1, 1);
	date_naissance_ = new wxDatePickerCtrl(hs4->GetStaticBox(), wxID_ANY);
	wxStaticText* dn = new wxStaticText(hs4->GetStaticBox(), wxID_ANY, wxT("تاريخ الإزدياد"), wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	dn->SetForegroundColour(*wxRED);
	lol->Add(v6[date_naissance], 0, wxALIGN_RIGHT, 2);
	lol->Add(dn, 0, wxALIGN_RIGHT, 2);
	lol->Add(tous_donnee[date_naissance], 1, wxEXPAND | wxALL, 2);
	lol->Add(date_naissance_, 1, wxEXPAND | wxALL, 2);
	
	//tous_donnee[nom_prenom] = new wxTextCtrl(hs4->GetStaticBox(), wxID_ANY, langue_francais[nom_prenom]);
	hss41->Add(v6[nom_prenom], 0, wxALIGN_RIGHT, 2);
	hss41->Add(tous_donnee[nom_prenom], 0, wxEXPAND | wxALL, 2);
	hss41->Add(lol, 1, wxEXPAND | wxALL, 2);
	hss41->Add(v6[adresse], 0, wxALIGN_RIGHT, 2);
	hss41->Add(tous_donnee[adresse], 1, wxEXPAND | wxALL, 2);
	wxFlexGridSizer* hss43_grid = new wxFlexGridSizer(4, 2, 2, 2);
	hss43_grid->AddGrowableCol(0, 1);
	hss43_grid->AddGrowableCol(1, 1);
	v6.push_back(new wxStaticText(hs4->GetStaticBox(), wxID_ANY, langue_francais[nationalite]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4->GetStaticBox(), wxID_ANY, langue_francais[num_piece_identite]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4->GetStaticBox(), wxID_ANY, langue_francais[email]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4->GetStaticBox(), wxID_ANY, wxT("الحالة الإجتماعية")));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	tous_donnee[num_piece_identite] = new wxTextCtrl(hs4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	tous_donnee[num_piece_identite]->SetHint(langue_francais[num_piece_identite]);
	tous_donnee[nationalite] = new wxTextCtrl(hs4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	tous_donnee[nationalite]->SetHint(langue_francais[nationalite]);
	tous_donnee[email] = new wxTextCtrl(hs4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	tous_donnee[email]->SetHint(langue_francais[email]);
	situation_familiale = new wxChoice(hs4->GetStaticBox(), ID_SITUATION_FAMILIALE, 
		wxDefaultPosition, wxDefaultSize, 4, situation_familiale_list);
	hss43_grid->Add(v6[adresse + 2], 0, wxALIGN_RIGHT, 2);
	hss43_grid->Add(v6[adresse + 1], 0, wxALIGN_RIGHT, 2);
	hss43_grid->Add(tous_donnee[num_piece_identite], 0, wxEXPAND | wxALL, 2);
	hss43_grid->Add(tous_donnee[nationalite], 0, wxEXPAND | wxALL, 2);
	hss43_grid->Add(v6[adresse + 4], 0, wxALIGN_RIGHT, 2);
	hss43_grid->Add(v6[adresse + 3], 0, wxALIGN_RIGHT, 2);
	hss43_grid->Add(situation_familiale, 0, wxEXPAND | wxALL, 2);
	hss43_grid->Add(tous_donnee[email], 0, wxEXPAND | wxALL, 2);
	hss41->Add(hss43_grid, 0, wxEXPAND | wxALL, 2);

	v6.push_back(new wxStaticText(hs4->GetStaticBox(), wxID_ANY, wxT("ولاية")));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4->GetStaticBox(), wxID_ANY, wxT("هاتف")));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	sb = new wxBitmapButton(hs4->GetStaticBox(), modifier_photo_id, wxBitmap(wxT("no_photo.jpg"), wxBITMAP_TYPE_JPEG));
	sb->SetLabel(wxT("no_photo.jpg"));
	wilaya = new wxChoice(hs4->GetStaticBox(), ID_SITUATION_FAMILIALE,
		wxDefaultPosition, wxDefaultSize, 48, wilaya_list);
	tous_donnee[telephone] = new wxTextCtrl(hs4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT);
	tous_donnee[telephone]->SetHint(langue_francais[telephone]);
	hss42->Add(sb, 1, wxEXPAND | wxALL, 2);
	hss42->Add(v6[adresse + 5], 0, wxALIGN_RIGHT, 2);
	hss42->Add(wilaya, 0, wxEXPAND | wxALL, 2);
	hss42->Add(v6[adresse + 6], 0, wxALIGN_RIGHT, 2);
	hss42->Add(tous_donnee[telephone], 0, wxEXPAND | wxALL, 2);
	wxFlexGridSizer* hss44_grid = new wxFlexGridSizer(2, 6, 2, 2);
	hss44_grid->AddGrowableCol(0, 1);
	hss44_grid->AddGrowableCol(1, 1);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[groupe_sanguin]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[taille]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[poid]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[vue]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[sex]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[age]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	v6.push_back(new wxStaticText(hs4g->GetStaticBox(), wxID_ANY, langue_francais[test_medical]));
	v6[v6.size() - 1]->SetForegroundColour(*wxRED);
	tous_donnee[test_medical] = new wxTextCtrl(hs4g->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_RIGHT|wxTE_MULTILINE);
	taille_spin = new wxSpinCtrl(hs4g->GetStaticBox(), wxID_ANY, langue_francais[taille], wxDefaultPosition,
		wxDefaultSize, wxSP_ARROW_KEYS, taille_min, taille_max, 160);
	poid_spin = new wxSpinCtrl(hs4g->GetStaticBox(), wxID_ANY, langue_francais[poid], wxDefaultPosition,
		wxDefaultSize, wxSP_ARROW_KEYS, poid_min, poid_max, 80);
	sex_choix = new wxChoice(hs4g->GetStaticBox(), wxID_ANY, wxDefaultPosition,
		wxDefaultSize, sex_femme + 1, sex_francais);
	sex_choix->SetSelection(sex_homme);
	age_spin = new wxSpinCtrl(hs4g->GetStaticBox(), ID_AGE, langue_francais[age], wxDefaultPosition,
		wxDefaultSize, wxSP_ARROW_KEYS, age_min, age_max, 25);
	vue_spin = new wxSpinCtrl(hs4g->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition,
		wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 8);
	groupe_sanguin_choix = new wxChoice(hs4g->GetStaticBox(), wxID_ANY, wxDefaultPosition,
		wxDefaultSize, o_moin + 1, groupe_sanguin_francais);
	groupe_sanguin_choix->SetSelection(a_plus);
	hss44_grid->Add(v6[adresse + 7], 0, wxALIGN_RIGHT, 2);
	hss44_grid->Add(v6[adresse + 8], 0, wxALIGN_RIGHT, 2);
	hss44_grid->Add(v6[adresse + 9], 0, wxALIGN_RIGHT, 2);
	hss44_grid->Add(v6[adresse + 10], 0, wxALIGN_RIGHT, 2);
	hss44_grid->Add(v6[adresse + 11], 0, wxALIGN_RIGHT, 2);
	hss44_grid->Add(v6[adresse + 12], 0, wxALIGN_RIGHT, 2);
	hss44_grid->Add(groupe_sanguin_choix, 1, wxEXPAND | wxALL, 2);
	hss44_grid->Add(taille_spin, 1, wxEXPAND | wxALL, 2);
	hss44_grid->Add(poid_spin, 1, wxEXPAND | wxALL, 2);
	hss44_grid->Add(vue_spin, 1, wxEXPAND | wxALL, 2);
	hss44_grid->Add(sex_choix, 1, wxEXPAND | wxALL, 2);
	hss44_grid->Add(age_spin, 1, wxEXPAND | wxALL, 2);
	
	hs4->Add(hss41, 1, wxEXPAND | wxALL, 2);
	hs4->Add(hss42, 1, wxEXPAND | wxALL, 2);
	
	hs4g->Add(hs4, 1, wxEXPAND | wxALL, 2);
	hs4g->Add(hss44_grid, 0, wxEXPAND | wxUP, 15);
	hs4g->Add(v6[adresse + 13], 0, wxALIGN_RIGHT | wxALL, 2);
	hs4g->Add(tous_donnee[test_medical], 1, wxEXPAND | wxALL, 2);
	//-------------------------------
	global_sizer->Add(hs0, 1, wxEXPAND | wxALL, 2);
	global_sizer->Add(hs1, 1, wxCENTER | wxALL, 2);
	global_mid_sizer->Add(hs2, 1, wxEXPAND | wxALL, 2);
	global_mid_sizer->Add(hs4g, 1, wxEXPAND | wxALL, 2);
	global_sizer->Add(global_mid_sizer, 1, wxEXPAND | wxALL, 2);
	global_sizer->Add(hs3, 0, wxALL | wxCENTER, 2);
	SetSizer(global_sizer);
}

//-------------------------------------------

class myapp : public wxApp
{
public :
	virtual bool OnInit();
};

DECLARE_APP(myapp)
IMPLEMENT_APP(myapp)

bool myapp::OnInit()
{
	interface_de_donnee* frame = new interface_de_donnee();
	frame->Show(true);
	return true;
}