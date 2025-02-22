#include <iostream>
#include <iomanip>
#include <conio.h>
#include <antheaderPlusPlus.h>
#include <fstream>
#include <filesystem>

using namespace std;

class stock{
	
	public:
		int barcode;
		char pro_name[30];
		float price;
		int qty = 0;
		string category;
		
	public:
		double SubTotal(){
			return price * qty;
		}
	
	public:
		static void header(){
			//line upper
			cout << "\n\t";
			for(int i = 1; i <= 88; i++){
				cout << "-";
			}
			//header 
			cout << "\n\n\t" << left;
			cout << setw(10) << "Barcode";
			cout << setw(30) << "Products Name";
			cout << setw(15) << "Category";
			cout << setw(10) << "Price";
			cout << setw(10) << "Quantity";
			cout << setw(10) << "Sub Total";
			
			
		}
		
		static void footer(){
			
			cout << "\n\t\t\t\t   --------- Windows Store MS ---------";
			
		}
		
		void register_Product(){
			
			cout << "\n\t\t ---------------- Register Products ----------------\n";
			cout << "\n\t\t Register Barcode      : "; cin >> barcode; fflush(stdin); cin.clear();
			cout << "\n\t\t Register Product name : "; cin.get(pro_name,30); fflush(stdin);
			cout << "\n\t\t Register Category     : "; getline(cin,category); fflush(stdin);
			cout << "\n\t\t Register Price        : "; cin >> price; fflush(stdin); cin.clear();
			
		}
		
		void importQTY(){
			
			int qtyImport;
			cout << "\n\t\t ---------------- Import Products ----------------\n";
			cout << "\n\t\t Enter Quantity : "; cin >> qtyImport; fflush(stdin); cin.clear();
			
			// Cal
			qty += qtyImport;
			
		}
		
		void display(){
			
			cout << "\n\n\t";
			for(int i = 1; i <= 88; i++){
				cout << "-";
			}
			
			cout << "\n\n\t" << left << fixed << setprecision(2);
			cout << setw(10) << barcode;
			cout << setw(30) << pro_name;
			cout << setw(15) << category;
			cout << setw(10) << "$" + int_string(price);
			cout << setw(10);
			if(qty==0){
			cout<<"OFS";
			cout << setw(10) << "$" + int_string(SubTotal()) << endl;
			}
			
			
		}
		
};

//////////////////////////////////////////////
// global Object
stock st;
fstream File_stock;

// None member function
//////////////////////////////////////////////
void Register_ToFile(){
	
	File_stock.open("stock.bin", ios::out | ios::app | ios::binary);
	
	st.register_Product();
	
	File_stock.write((char*)&st, sizeof(st));
	
	File_stock.close();
}

void view_data(){
	
	File_stock.open("stock.bin", ios::in | ios::binary);
	
	if(File_stock.fail()){
		
		cout << "\n\t File not found";
		
	}
	
//	if(File_stock.good()){
//		
//		File_stock.read((char*)&st, sizeof(st));
//		
//		// first solution
////		stock::header();
////		while(File_stock.eof() != true){
////			
////			st.display();
////			File_stock.read((char*)&st, sizeof(st));
////			
////		}
//		
//		//  second solution
//		// find items in stock by file devide with object
//		int n = filesystem::file_size("stock.bin") / sizeof(st);
//		
//		stock::header();
//		for(int i = 1; i <= n; i++){
//			
//			st.display();
//			File_stock.read((char*)&st, sizeof(st));
//		}
//		
//	}
	
	File_stock.close();
	
}
void SearchByCateg(){
	File_stock.open("stock.bin",ios::in | ios::binary);
	if(File_stock.fail()){
		cout<<"\n\t File not found!";	
	}
	
	if(File_stock.good()){
		string searchCateg;
		bool isfound;
		cout<<"\n\t -> Enter Category to seacrch :";
		getline(cin,searchCateg);fflush(stdin);
		File_stock.read((char*)&st,sizeof(st));
		stock::header();
		while(File_stock.eof()!=true){
			
			if(searchCateg == st.category){
				st.display();
				isfound=true;	
			}
			
			File_stock.read((char*)&st,sizeof(st));
		}
		if(isfound==false){
			cout<<"\n\t search Category not found!";
		}
	}
	File_stock.close();
}
void import_stock_toFile(){
	ofstream File_StB;
	File_stock.open("stock.bin",ios::in | ios::binary);
	File_StB.open ("stockBackup.bin",ios::out | ios::binary);
	
	if(!File_stock){
		cout<<"\n\t File not found";
	}
	if(File_stock.good()){
		int Sbar;
		bool isFound;
		cout<<"\n\t -> Enter Barcode to import :";cin>>Sbar;fflush(stdin);cin.clear();
		File_stock.read((char*)&st,sizeof(st));
		while(File_stock.eof()!=true){ 
			//CONDITION IF SEARCH BARCODE
			if(Sbar==st.barcode){
				st.importQTY();
				File_StB.write((char*)&st,sizeof(st));
				isFound=true;
			} 
			if(Sbar!=st.barcode){
				File_StB.write((char*)&st,sizeof(st));
			}
			File_stock.read((char*)&st,sizeof(st));
		}
		if(isFound==false){
			cout<<"\n\n\t Barcode is not in stock";
		}
		if(isFound==true){
			cout<<"\n\n\t Import successfulll";
		}
	}
	File_stock.close();
	File_StB.close();
	remove("File_stock.bin");
	rename("File_StB.bin","File_stock.bin");
	}
	
	
	void update(){
		File_stock.open("stock.bin",ios::in | ios::out |ios::binary);
		if(File_stock.fail()){
			cout<<"\n\t File not found!";
		}
		if(File_stock.good()){
			int searchBar;
			bool isUpdated;
			cout<<"\n\t Enter Barcode for Update:";
			cin>>searchBar;fflush(stdin);cin.clear();
			File_stock.read((char*)&st,sizeof(st));
			while(File_stock.eof()!=true){
				if(searchBar==st.barcode){
					int lastbyte = File_stock.tellg();
					cout<<"\n\t ----------UPDATE PRODUCT INFO------------";
					cout<<"\n\t Update Barcode:",cin>>st.barcode;fflush(stdin);cin.clear();
					cout<<"\n\t Update Pro_name:";cin.get(st.pro_name,30);fflush(stdin);
					cout<<"\n\t Update Price:";cin>>st.price;fflush(stdin);cin.clear();
					cout<<"\n\t Update Category:";getline(cin,st.category);fflush(stdin);
					
					File_stock.seekp(lastbyte - sizeof(st));
					File_stock.write((char*)&st,sizeof(st));
					isUpdated=true;
					
				}
				File_stock.read((char*)&st,sizeof(st));
			}
			if(isUpdated==false){
				cout<<"\n\t Update Unsuccess";
			}
			if(isUpdated==true){
				cout<<"\n\t Update Successful";
			}
		}
		File_stock.close();
	}
	
	void sortByBar(){
		File_stock.open("stock.bin",ios::in | ios::out | ios::binary);
		if(File_stock.fail()){
			cout<<"\n\t File not found!";
		}
		int n= 0;
		File_stock.seekg(0,ios::end);
		n=File_stock.tellg()/sizeof(st);
		File_stock.seekg(0,ios::beg);
		stock* StockArray = new stock[n];
		File_stock.read((char*)StockArray,sizeof(st)*n);
		for(int i=0;i<n;i++){
			for(int j=0;j<n-i-1;i++){
				if(StockArray[j].barcode < StockArray[j+1].barcode){
					stock temp = StockArray[j];
					StockArray[j+1] = StockArray[j];
					StockArray[j+1] = temp;
				}
			}
		}
		File_stock.seekp(0,ios::beg);
		File_stock.write((char*)StockArray, sizeof(st)*n);
		File_stock.close();
		
		delete[]StockArray;
		cout<<"Sort Sucess";
		
	}

int main(){
	
	chAgain:
	cls();
	char option;
	// MainBox
	drawBoxDoubleLineWithBG(32, 1, 55, 20, 23);
// title box
	drawBoxSingleLineWithBG(47, 2, 29, 1, 169);
	gotoxy(48, 3); cout << "  WS    MANAGEMENT SYSTEM";
// menu box 
	drawBoxSingleLineWithBG(37, 6, 45, 1, 169);
	gotoxy(49, 7); cout << "[1] - REGISTER PRODUCT";
	drawBoxSingleLineWithBG(37, 9, 45, 1, 169);
	gotoxy(49, 10); cout << "[2] - DISPLAY QUANTITY";
	drawBoxSingleLineWithBG(37, 12, 45, 1, 169);
	gotoxy(49, 13); cout << "[3] - SEARCH QUANTITY";
	drawBoxSingleLineWithBG(37, 15, 45, 1, 169);
	gotoxy(49, 16); cout << "[4] - IMPORT BARCODE";
	drawBoxSingleLineWithBG(37, 18, 45, 1, 169);
	gotoxy(49, 19); cout << "[5] - UPDATE BARCODE";

	foreColor(169);					
	gotoxy(32, 21); cout << "          Please choose one menu just press key        ";					
		// clear color 
	foreColor(7);					
	
	option = getch();
	
	switch(option){
		
		case '1':{
			
			do{
				
				cls();
				setcursor(true, 20);
				Register_ToFile();
				cout << "\n\t\t Registered Success!";
				delay(800);
				cout << "\n\t\t Press [ESC] back to Menu or Press any key Input again";
			}while(getch() != 27);
			cls();
			goto chAgain;
			
			break;
		}
		
		case '2':{
			
			do{
				
				cls();
				setcursor(false, 0);
				view_data();
				stock::footer();
			}while(!getch());
			
			cls();
			goto chAgain;
			
			break;
		}
		case'3':{
				do{
				
				cls();
				setcursor(true, 20);
				view_data();
				stock::footer();
			}while(!getch());
			
			cls();
			goto chAgain;
			
			break;
	}
		case'4':{
				do{
				cls();
				setcursor(true, 20);
				import_stock_toFile();
				stock::footer();
			}while(!getch());
			
			cls();
			goto chAgain;
			
			break;
	}
			
		default:{
			
			cls();
			cout << "\n\t Wrong choice!!" << endl;
			cout << "\n\t Please choose again";
			delay(1500);
			goto chAgain;
			
			break;
		}
		
	}
	
}