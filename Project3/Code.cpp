#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

class Page {
	public:
		string id;
		int count;
		
		int find(vector<Page> list, string s) {
			for (int i = 0; i < list.size(); i++) {
				if (list[i].id == s) return i;
			}
			return -1;
		}
		
		void readFile(string & infilename, vector<Page> & list, int & command, int & frame) {
			int id;
			string s;
			ifstream infile;
			infile.open( infilename.c_str(), ios::in );
			while(!infile) {
				cout << "檔案不存在!!!" << endl;
				cout << endl << "請輸入檔案名稱:" << endl;
				cin >>  infilename;	
				infile.open( infilename.c_str(), ios::in );
			}
			infile >> command >> frame;
			
			getline(infile, s);  // get enter
			getline(infile, s);  // get line 
			
			for (int i = 0; i < s.size(); i++) {
				Page *temp = new Page();
				list.push_back(*temp);
		    	list[list.size()-1].id = s[i];
		    	list[list.size()-1].count = 0;
			}
			infile.close();
		}
		
		void FIFO(vector<Page> list, int frame, int & replace, vector<string> & pageFrame, vector<int> & fault) {
			vector<Page> q;
			string s;
			for(int i = 0; i < list.size(); i++) {
				if (find(q, list[i].id) == -1) {  // not in queue 
					fault.push_back(i);
					if (q.size() == frame) {
						replace++;
						q.pop_back ();
					}
					Page *temp = new Page();
					q.insert(q.begin(), *temp);
					q[0].id = list[i].id;
				}
				for (int j = 0; j < q.size(); j++) s = s + q[j].id;
				pageFrame.push_back(s);
				s.clear();
			}
		}
		
		void LRU(vector<Page> list, int frame, int & replace, vector<string> & pageFrame, vector<int> & fault) {
			vector<Page> q;
			string s, str;
			int index = 0;
			for(int i = 0; i < list.size(); i++) {
				index = find(q, list[i].id);
				if (index == -1) {  // not in queue 
					fault.push_back(i);
					if (q.size() == frame) {
						replace++;
						q.pop_back ();
					}
					Page *temp = new Page();
					q.insert(q.begin(), *temp);
			    	q[0].id = list[i].id;
				}
				else {
					Page temp = q[index];
					q.erase(q.begin() + index);
					q.insert(q.begin(), temp);
				}
				for (int j = 0; j < q.size(); j++) s += q[j].id;
				pageFrame.push_back(s);
				s.clear();
			}
		}
		
		void LFULRU(vector<Page> list, int frame, int & replace, vector<string> & pageFrame, vector<int> & fault) {
			vector<Page> q;
			string s;
			int index = 0, min;
			for(int i = 0; i < list.size(); i++) {
				index = find(q, list[i].id);
				if (index == -1) {  // not in queue 
					fault.push_back(i);
					if (q.size() == frame) {
						min = q[0].count;
						for (int j = 0; j < q.size(); j++) {
							if (q[j].count < min) min = q[j].count;
						}
						for (int j = q.size()-1 ; j >= 0; j--) {
							if (q[j].count == min) {
								q.erase(q.begin() + j);
								break;
							}
						}
						replace++;
					}
					Page *temp = new Page();
					q.insert(q.begin(), *temp);
			    	q[0].id = list[i].id;
			    	q[0].count = 1;
				}
				else {
					Page temp = q[index];
					q.erase(q.begin() + index);
					q.insert(q.begin(), temp);
					q[0].count++;
				}
				for (int j = 0; j < q.size(); j++) s += q[j].id;
				pageFrame.push_back(s);
				s.clear();
			}
		}
		
		void MFUFIFO(vector<Page> list, int frame, int & replace, vector<string> & pageFrame, vector<int> & fault) {
			vector<Page> q;
			string s;
			int index = 0, max;
			for(int i = 0; i < list.size(); i++) {
				index = find(q, list[i].id);
				if (index == -1) {  // not in queue 
					fault.push_back(i);
					if (q.size() == frame) {
						max = q[0].count;
						for (int j = 0; j < q.size(); j++) {
							if (q[j].count > max) max = q[j].count;
						}
						for (int j = q.size()-1 ; j >= 0; j--) {
							if (q[j].count == max) {
								q.erase(q.begin() + j);
								break;
							}
						}
						replace++;
					}
					Page *temp = new Page();
					q.insert(q.begin(), *temp);
			    	q[0].id = list[i].id;
			    	q[0].count = 1;
				}
				else {
					q[index].count++;
				}
				for (int j = 0; j < q.size(); j++) s += q[j].id;
				pageFrame.push_back(s);
				s.clear();
			}
		}
		
		void MFULRU(vector<Page> list, int frame, int & replace, vector<string> & pageFrame, vector<int> & fault) {
			vector<Page> q;
			string s;
			int index = 0, max;
			for(int i = 0; i < list.size(); i++) {
				index = find(q, list[i].id);
				if (index == -1) {  // not in queue 
					fault.push_back(i);
					if (q.size() == frame) {
						max = q[0].count;
						for (int j = 0; j < q.size(); j++) {
							if (q[j].count > max) max = q[j].count;
						}
						for (int j = q.size()-1 ; j >= 0; j--) {
							if (q[j].count == max) {
								q.erase(q.begin() + j);
								break;
							}
						}
						replace++;
					}
					Page *temp = new Page();
					q.insert(q.begin(), *temp);
			    	q[0].id = list[i].id;
			    	q[0].count = 1;
				}
				else {
					Page temp = q[index];
					q.erase(q.begin() + index);
					q.insert(q.begin(), temp);
					q[0].count++;
				}
				for (int j = 0; j < q.size(); j++) s += q[j].id;
				pageFrame.push_back(s);
				s.clear();
			}
		}
		
		void writeFile(string outfilename, int command, int replace, int frame, vector<Page> list, vector<string> pageFrame, vector<int> fault) {
			ofstream outfile;
			outfile.open(outfilename.c_str(), ios::out);
			int size = fault.size();
			
			if (command == 1) outfile << "--------------FIFO-----------------------" << endl;
			else if (command == 2) outfile << "--------------LRU-----------------------" << endl;
			else if (command == 3) outfile << "--------------Least Frequently Used LRU Page Replacement-----------------------" << endl;
			else if (command == 4) outfile << "--------------Most Frequently Used Page Replacement -----------------------" << endl;
			else if (command == 5) outfile << "--------------Most Frequently Used LRU Page Replacement -----------------------" << endl;
					
			for (int i = 0; i < list.size(); i++) {
				outfile << list[i].id << "	" << pageFrame[i];
				if (fault.size() != 0 && fault[0] == i) {
					outfile << "	F";
					fault.erase(fault.begin());
				}
				outfile << endl;
			}
			
			outfile << "Page Fault = " << size << "  Page Replaces = " << replace << "  Page Frames = " << frame;
			
			outfile.close();
		}
		
		void writeFileAll(string outfilename, int command, int frame, vector<Page> list,
					 int FIFOreplace, int LRUreplace, int LFULRUreplace, int MFUFIFOreplace, int MFULRUreplace,
					 vector<string> FIFOpF, vector<string> LRUpF, vector<string> LFULRUpF, vector<string> MFUFIFOpF, vector<string> MFULRUpF,
					 vector<int> FIFOfault, vector<int> LRUfault, vector<int> LFULRUfault, vector<int> MFUFIFOfault, vector<int> MFULRUfault) {
					 	
			ofstream outfile;
			outfile.open(outfilename.c_str(), ios::out);
			int size1 = FIFOfault.size(), size2 = LRUfault.size(), size3 = LFULRUfault.size(), size4 = MFUFIFOfault.size(), size5 = MFULRUfault.size();
			
			outfile << "--------------FIFO-----------------------" << endl;		
			for (int i = 0; i < list.size(); i++) {
				outfile << list[i].id << "	" << FIFOpF[i];
				if (FIFOfault.size() != 0 && FIFOfault[0] == i) {
					outfile << "	F";
					FIFOfault.erase(FIFOfault.begin());
				}
				outfile << endl;
			}
			outfile << "Page Fault = " << size1 << "  Page Replaces = " << FIFOreplace << "  Page Frames = " << frame << endl;
			outfile << endl << "--------------LRU-----------------------" << endl;		
			for (int i = 0; i < list.size(); i++) {
				outfile << list[i].id << "	" << LRUpF[i];
				if (LRUfault.size() != 0 && LRUfault[0] == i) {
					outfile << "	F";
					LRUfault.erase(LRUfault.begin());
				}
				outfile << endl;
			}
			outfile << "Page Fault = " << size2 << "  Page Replaces = " << LRUreplace << "  Page Frames = " << frame << endl;
			outfile << endl << "--------------Least Frequently Used LRU Page Replacement-----------------------" << endl;		
			for (int i = 0; i < list.size(); i++) {
				outfile << list[i].id << "	" << LFULRUpF[i];
				if (LFULRUfault.size() != 0 && LFULRUfault[0] == i) {
					outfile << "	F";
					LFULRUfault.erase(LFULRUfault.begin());
				}
				outfile << endl;
			}
			outfile << "Page Fault = " << size3 << "  Page Replaces = " << LFULRUreplace << "  Page Frames = " << frame << endl;
			outfile << endl << "--------------Most Frequently Used Page Replacement -----------------------" << endl;		
			for (int i = 0; i < list.size(); i++) {
				outfile << list[i].id << "	" << MFUFIFOpF[i];
				if (MFUFIFOfault.size() != 0 && MFUFIFOfault[0] == i) {
					outfile << "	F";
					MFUFIFOfault.erase(MFUFIFOfault.begin());
				}
				outfile << endl;
			}
			outfile << "Page Fault = " << size4 << "  Page Replaces = " << MFUFIFOreplace << "  Page Frames = " << frame << endl;
			outfile << endl << "--------------Most Frequently Used LRU Page Replacement -----------------------" << endl;		
			for (int i = 0; i < list.size(); i++) {
				outfile << list[i].id << "	" << MFULRUpF[i];
				if (MFULRUfault.size() != 0 && MFULRUfault[0] == i) {
					outfile << "	F";
					MFULRUfault.erase(MFULRUfault.begin());
				}
				outfile << endl;
			}
			outfile << "Page Fault = " << size5 << "  Page Replaces = " << MFULRUreplace << "  Page Frames = " << frame;
			
			outfile.close();
		}
};

int main () {
	int command, frame;
	int replace = 0;
	string infilename, outfilename;
	vector<Page> list;
	vector<string> pF;
	vector<int> fault;
	Page p;
	do {
		list.clear();
		cout << endl << "請輸入檔案名稱:" << endl;
		cin >>  infilename;
		p.readFile(infilename, list, command, frame);
		outfilename = "out_" + infilename;
		switch(command) {
			case 0: break;
			case 1:{  // FIFO 
				p.FIFO(list, frame, replace, pF, fault);
				p.writeFile(outfilename, command, replace, frame,  list, pF, fault);
				
				break;
			} // case 1 
			case 2:{  // LRU 
				p.LRU(list, frame, replace, pF, fault);
				p.writeFile(outfilename, command, replace, frame,  list, pF, fault);
				
				break;
			} // case 2 
			case 3:{  // LFU + LRU  
				p.LFULRU(list, frame, replace, pF, fault);
				p.writeFile(outfilename, command, replace, frame,  list, pF, fault);
				
				break;
			} // case 3 
			case 4:{  // MFU + FIFO 
				p.MFUFIFO(list, frame, replace, pF, fault);
				p.writeFile(outfilename, command, replace, frame,  list, pF, fault);
				
				break;
			} // case 4 
			case 5:{  // MFU + LRU 
				p.MFULRU(list, frame, replace, pF, fault);
				p.writeFile(outfilename, command, replace, frame,  list, pF, fault);
				
				break;
			} // case 5 
			case 6:{  // ALL 	
				int FIFOreplace = 0, LRUreplace = 0, LFULRUreplace = 0, MFUFIFOreplace = 0, MFULRUreplace = 0;
				vector<string> FIFOpF, LRUpF, LFULRUpF, MFUFIFOpF, MFULRUpF;
				vector<int> FIFOfault, LRUfault, LFULRUfault, MFUFIFOfault, MFULRUfault;
				
				p.FIFO(list, frame, FIFOreplace, FIFOpF, FIFOfault);
				p.LRU(list, frame, LRUreplace, LRUpF, LRUfault);
				p.LFULRU(list, frame, LFULRUreplace, LFULRUpF, LFULRUfault);
				p.MFUFIFO(list, frame, MFUFIFOreplace, MFUFIFOpF, MFUFIFOfault);
				p.MFULRU(list, frame, MFULRUreplace, MFULRUpF, MFULRUfault);
				
				p.writeFileAll(outfilename, command, frame, list,
								FIFOreplace, LRUreplace, LFULRUreplace, MFUFIFOreplace, MFULRUreplace,
								FIFOpF, LRUpF, LFULRUpF, MFUFIFOpF, MFULRUpF,
								FIFOfault, LRUfault, LFULRUfault, MFUFIFOfault, MFULRUfault);
				
				break;
			} // case 6 
			default: cout << endl << "Command does not exist!" << endl;
		} // switch*/
		
		list.clear();
		pF.clear();
		fault.clear();
		replace = 0;
	} while (command != 0);	
		
	system("pause");
	return 0;
}
