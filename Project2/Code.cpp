#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

int sTime = 0;

class Time {
	public:
		int command;
		int id;
		int time;    // waiting time or turnaround time 
		
		void writeFile(string outfilename, int command, vector<Time> wt, vector<Time> tat, vector<string> gantt) {
	
			for (int i = 0; i < wt.size(); i++)   // Sorted waiting time by PID 
				for (int j = 0; j < wt.size(); j++) 
					if (wt[i].id < wt[j].id) swap(wt[i], wt[j]);
				
			for (int i = 0; i < tat.size(); i++)   // Sorted turnaround time by PID 
			   	for (int j = 0; j < tat.size(); j++) 
					if (tat[i].id < tat[j].id) swap(tat[i], tat[j]);
					
			ofstream outfile;
			outfile.open(outfilename.c_str(), ios::out);
			string method;
			if (command == 1) {
				method = "FCFS";
				outfile << "FCFS" << endl << "==        FCFS==" << endl;
			}
			else if (command == 2) {
				method = "RR";
				outfile << "RR" << endl << "==          RR==" << endl;
			}
			else if (command == 3) {
				method = "SRTF";
				outfile << "SRTF" << endl << "==        SRTF==" << endl;
			}
			else if (command == 4) {
				method = "PPRR";
				outfile << "Priority RR" << endl << "==        PPRR==" << endl;
			}
			else if (command == 5) {
				method = "HRRN";
				outfile << "HRRN" << endl << "==        HRRN==" << endl;
			}
			
			for (int i = 0; i < gantt.size(); i++) outfile << gantt[i];
			outfile << endl << "===========================================================" << endl << endl;
			
			outfile << "Waiting Time" << endl << "ID\t" << method << endl << "===========================================================" << endl;
			for (int i = 0; i < wt.size(); i++) outfile << wt[i].id << "\t" << wt[i].time << endl;
			outfile << "===========================================================" << endl << endl;
			
			outfile << "Turnaround Time" << endl << "ID\t" << method << endl << "===========================================================" << endl;
			for (int i = 0; i < tat.size(); i++) outfile << tat[i].id << "\t" << tat[i].time << endl;
			outfile << "===========================================================" << endl << endl;
			
			outfile.close();
		}
		
		void writeFileAll(string outfilename, int command, vector<Time> FCFSwt, vector<Time> RRwt, vector<Time> SRTFwt, vector<Time> PPRRwt, vector<Time> HRRNwt, 
							vector<Time> FCFStat, vector<Time> RRtat, vector<Time> SRTFtat, vector<Time> PPRRtat, vector<Time> HRRNtat, 
							vector<string> FCFSgantt, vector<string> RRgantt, vector<string> SRTFgantt, vector<string> PPRRgantt, vector<string> HRRNgantt) {
								
			for (int i = 0; i < FCFSwt.size(); i++) {  // Sorted waiting time by PID 
				for (int j = 0; j < FCFSwt.size(); j++) {
					if (FCFSwt[i].id < FCFSwt[j].id) swap(FCFSwt[i], FCFSwt[j]);
					if (RRwt[i].id < RRwt[j].id) swap(RRwt[i], RRwt[j]);
					if (SRTFwt[i].id < SRTFwt[j].id) swap(SRTFwt[i], SRTFwt[j]);
					if (PPRRwt[i].id < PPRRwt[j].id) swap(PPRRwt[i], PPRRwt[j]);
					if (HRRNwt[i].id < HRRNwt[j].id) swap(HRRNwt[i], HRRNwt[j]);
				}
			}
				
			for (int i = 0; i < FCFStat.size(); i++) {  // Sorted turnaround time by PID 
				for (int j = 0; j < FCFStat.size(); j++) {
					if (FCFStat[i].id < FCFStat[j].id) swap(FCFStat[i], FCFStat[j]);
					if (RRtat[i].id < RRtat[j].id) swap(RRtat[i], RRtat[j]);
					if (SRTFtat[i].id < SRTFtat[j].id) swap(SRTFtat[i], SRTFtat[j]);
					if (PPRRtat[i].id < PPRRtat[j].id) swap(PPRRtat[i], PPRRtat[j]);
					if (HRRNtat[i].id < HRRNtat[j].id) swap(HRRNtat[i], HRRNtat[j]);
				}
			}
			ofstream outfile;
			outfile.open(outfilename.c_str(), ios::out);
			
			outfile << "All" << endl;
			outfile << "==        FCFS==" << endl;
			for (int i = 0; i < FCFSgantt.size(); i++) outfile << FCFSgantt[i];
			outfile << endl << "==          RR==" << endl;
			for (int i = 0; i < RRgantt.size(); i++) outfile << RRgantt[i];
			outfile << endl << "==        SRTF==" << endl;
			for (int i = 0; i < SRTFgantt.size(); i++) outfile << SRTFgantt[i];
			outfile << endl << "==        PPRR==" << endl;
			for (int i = 0; i < PPRRgantt.size(); i++) outfile << PPRRgantt[i];
			outfile << endl << "==        HRRN==" << endl;
			for (int i = 0; i < HRRNgantt.size(); i++) outfile << HRRNgantt[i];
			outfile << endl << "===========================================================" << endl << endl;
			
			outfile << "Waiting Time" << endl << "ID\tFCFS\tRR\tSRTF\tPPRR\tHRRN" << endl << "===========================================================" << endl;
			for (int i = 0; i < FCFSwt.size(); i++) outfile << FCFSwt[i].id << "\t" << FCFSwt[i].time << "\t" << RRwt[i].time << "\t" << 
														SRTFwt[i].time << "\t" << PPRRwt[i].time << "\t" << HRRNwt[i].time << endl;
			outfile << "===========================================================" << endl << endl;
			
			outfile << "Turnaround Time" << endl << "ID\tFCFS\tRR\tSRTF\tPPRR\tHRRN" << endl << "===========================================================" << endl;
			for (int i = 0; i < FCFStat.size(); i++) outfile << FCFStat[i].id << "\t" << FCFStat[i].time << "\t" << RRtat[i].time << "\t" << 
														SRTFtat[i].time << "\t" << PPRRtat[i].time << "\t" << HRRNtat[i].time << endl;
			outfile << "===========================================================" << endl << endl;
			
			outfile.close();
		}
}; 

class Process {
	public:
		int id;
		int burst;
		int arrival;
		int priority, slice;  // for PPRR 
		int remain;  // Remaining Time 
		int ratio;   // Response Ratio for HRRN 
		
		vector<string> table = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
								"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
								
		void readFile(string infilename, vector<Process> & list, int & command, int & time_slice) {
			int id, burst, arrival, priority;
			string s;
			char ch;
			ifstream infile;
			infile.open( infilename.c_str(), ios::in );
			while(!infile) {
				cout << "檔案不存在!!!" << endl;
				cout << endl << "請輸入檔案名稱:" << endl;
				cin >>  infilename;	
				infile.open( infilename.c_str(), ios::in );
			}
			infile >> command >> time_slice;
			
			getline(infile, s);  // get enter
			getline(infile, s);  // get line 
			
		    while (infile >> id >> burst >> arrival >> priority) {
		    	Process *temp = new Process();
		    	list.push_back(*temp);
		    	list[list.size()-1].id = id;
		    	list[list.size()-1].burst = burst;
		    	list[list.size()-1].arrival = arrival;
		    	list[list.size()-1].priority = priority;
		    	list[list.size()-1].remain = burst;
		    	list[list.size()-1].slice = time_slice;
		    	
			}
			infile.close();
			
		    for (int i = 0; i < list.size(); i++) {  // Sorted by Arrival Time PID 
		    	for (int j = 0; j < list.size(); j++) {
					if (list[i].arrival < list[j].arrival) swap(list[i], list[j]);
					else if (list[i].arrival == list[j].arrival) {
						if (list[i].id < list[j].id) swap(list[i], list[j]);
					}
				}
			}
		}
		
		void FCFS(vector<Process> list, vector<Time> & wt, vector<Time> & tat, vector<string> & gantt) {
			int i = 0;
			while (i < list.size()) {
				while (sTime < list[i].arrival) {    // no process running 
					gantt.push_back("-");
					sTime++;
				}
				
				sTime += list[i].burst;
					
				Time *ttemp = new Time();
		    	tat.push_back(*ttemp);
		    	tat[tat.size()-1].command = 1;
		    	tat[tat.size()-1].id = list[i].id;
		    	tat[tat.size()-1].time = sTime - list[i].arrival;
		    		
				Time *wtemp = new Time();
		    	wt.push_back(*wtemp);
		    	wt[wt.size()-1].command = 1;
		    	wt[wt.size()-1].id = list[i].id;
		    	wt[wt.size()-1].time =  tat[tat.size()-1].time - list[i].burst;
		    	
		    	for (int j = 0; j < list[i].burst; j++) 
					gantt.push_back(table[list[i].id]);
					
				i++;
			}
		}
		
		void RR(vector<Process> list, int time_slice, vector<Time> & wt, vector<Time> & tat, vector<string> & gantt) {
			vector<Process> queue;
			
			while (list.size() != 0 || queue.size() != 0) {
				if (queue.size() == 0) {   // no process running
					while (sTime < list[0].arrival) {	
						gantt.push_back("-");
						sTime++;
					}
					while ( sTime >= list[0].arrival && list.size() != 0 ) {
						queue.push_back(list[0]);
						list.erase(list.begin());	 
					} // while
				}
				if (queue[0].remain - time_slice <= 0) {   // Finish 
					sTime += queue[0].remain;
					while ( sTime >= list[0].arrival && list.size() != 0 ) {
						queue.push_back(list[0]);
						list.erase(list.begin());	 
					} // while
					
					// tat
					Time *ttemp = new Time();
			    	tat.push_back(*ttemp);
			    	tat[tat.size()-1].command = 2;
			    	tat[tat.size()-1].id = queue[0].id;
			    	tat[tat.size()-1].time = sTime - queue[0].arrival;
			    	
		    		// wt 
					Time *wtemp = new Time();
			    	wt.push_back(*wtemp);
			    	wt[wt.size()-1].command = 2;
			    	wt[wt.size()-1].id = queue[0].id;
			    	wt[wt.size()-1].time =  tat[tat.size()-1].time - queue[0].burst;
			    	
					// gantt
					for (int i = 0; i < queue[0].remain; i++) 
						gantt.push_back(table[queue[0].id]);
						
					// pop from queue 
					queue.erase(queue.begin()) ;
				}
				else {
					queue[0].remain -= time_slice;
					// gantt
					for (int i = 0; i < time_slice; i++) 
						gantt.push_back(table[queue[0].id]);
						
					sTime += time_slice;
					while ( sTime >= list[0].arrival && list.size() != 0 ) {
						queue.push_back(list[0]);
						list.erase(list.begin());	 
					} // while
					
					// put current process into the end of queue 
					Process p = queue.front();
					queue.erase(queue.begin()) ;
					queue.push_back(p);
					
				}
			}
		}
		
		void SRTF(vector<Process> list, vector<Time> & wt, vector<Time> & tat, vector<string> & gantt) {
			vector<Process> queue;
			for (int i = 0; i < list.size(); i++) {  // Sorted by Arrival Time, CPU Burst, PID 
			   	for (int j = 0; j < list.size(); j++) {
			   		if (list[i].arrival < list[j].arrival) swap(list[i], list[j]);
					else if (list[i].arrival == list[j].arrival) {
						if (list[i].remain < list[j].remain) swap(list[i], list[j]);
						else if (list[i].remain == list[j].remain) {
							if (list[i].id < list[j].id) swap(list[i], list[j]);
						}
					}
				}
			}
			
			while (list.size() != 0 || queue.size() != 0) {
				if (queue.size() == 0) {   // no process running
					while (sTime < list[0].arrival) {	
						gantt.push_back("-");
						sTime++;
					}
					while ( sTime >= list[0].arrival && list.size() != 0 ) {
						queue.push_back(list[0]);
						list.erase(list.begin());	 
					} // while
				}
				if (queue[0].remain - 1 <= 0) {   // Finish 
					sTime++;
					
					// tat
					Time *ttemp = new Time();
			    	tat.push_back(*ttemp);
			    	tat[tat.size()-1].command = 3;
			    	tat[tat.size()-1].id = queue[0].id;
			    	tat[tat.size()-1].time = sTime - queue[0].arrival;
			    	
		    		// wt 
					Time *wtemp = new Time();
			    	wt.push_back(*wtemp);
			    	wt[wt.size()-1].command = 3;
			    	wt[wt.size()-1].id = queue[0].id;
			    	wt[wt.size()-1].time =  tat[tat.size()-1].time - queue[0].burst;
			    	
					// gantt
					gantt.push_back(table[queue[0].id]);
						
					// pop from queue 
					queue.erase(queue.begin()) ;
				}
				else {
					queue[0].remain -= 1;
					// gantt
					gantt.push_back(table[queue[0].id]);
					sTime++;					
				}
				
				while ( sTime >= list[0].arrival && list.size() != 0 ) {
					queue.push_back(list[0]);
					list.erase(list.begin());
					
					for (int i = 0; i < queue.size(); i++) {  // Sorted by CPU Burst, Arrival Time, PID 
				    	for (int j = 0; j < queue.size(); j++) {
				    		if (queue[i].remain < queue[j].remain) swap(queue[i], queue[j]);
							else if (queue[i].remain == queue[j].remain) {
								if (queue[i].arrival < queue[j].arrival) swap(queue[i], queue[j]);
								else if (queue[i].arrival == queue[j].arrival) {
									if (queue[i].id < queue[j].id) swap(queue[i], queue[j]);
								}
							}
						}
					}
				} // while
			}
		}
		
		void PPRR(vector<Process> list, int time_slice, vector<Time> & wt, vector<Time> & tat, vector<string> & gantt) {
			vector<Process> queue;
			int slice = 0;  // current process remaining time_slice 
			int num = 0;  // the number of same priority process 
			bool check = 0;
			
			for (int i = 0; i < list.size(); i++) {  // Sorted by Arrival Time, Priority, PID 
			   	for (int j = 0; j < list.size(); j++) {
			   		if (list[i].arrival < list[j].arrival) swap(list[i], list[j]);
					else if (list[i].arrival == list[j].arrival) {
						if (list[i].priority < list[j].priority) swap(list[i], list[j]);
						else if (list[i].priority == list[j].priority) {
							if (list[i].id < list[j].id) swap(list[i], list[j]);
						}
					}
				}
			}
			
			while (list.size() != 0 || queue.size() != 0) {
				if (queue.size() == 0) {   // no process running
					while (sTime < list[0].arrival) {	
						gantt.push_back("-");
						sTime++;
					}
				}
				
				while ( sTime >= list[0].arrival && list.size() != 0 ) {    // new process come in 
					int o = 0;
					while (o < queue.size()) {    // Sorted by Priority, Arrival Time, PID
						if (list[0].priority < queue[o].priority) break;
						o++;
					}
					if (o != queue.size() && num != 1 && queue[0].slice != time_slice) {    // Preemptive RR 
						// put current process into the end of the same part of queue 
						queue[0].slice = time_slice;
						Process p = queue.front();
						queue.insert(queue.begin() + num, p);
						queue.erase(queue.begin()) ;
					}
					queue.insert(queue.begin() + o, list[0]);
					list.erase(list.begin());	 
				} // while
				
				num = 0;
				for (int i = 0; i < queue.size(); i++)    // calculate the number of same priority process 
					if (queue[i].priority == queue[0].priority) num++;
				
				if (queue[0].remain - 1 <= 0) {   // Finish 
					sTime++;
					
					// tat
					Time *ttemp = new Time();
			    	tat.push_back(*ttemp);
			    	tat[tat.size()-1].command = 4;
			    	tat[tat.size()-1].id = queue[0].id;
			    	tat[tat.size()-1].time = sTime - queue[0].arrival;
			    	
		    		// wt 
					Time *wtemp = new Time();
			    	wt.push_back(*wtemp);
			    	wt[wt.size()-1].command = 4;
			    	wt[wt.size()-1].id = queue[0].id;
			    	wt[wt.size()-1].time =  tat[tat.size()-1].time - queue[0].burst;
			    	
					// gantt
					gantt.push_back(table[queue[0].id]);
						
					// pop from queue 
					queue.erase(queue.begin()) ;
					queue[0].slice = time_slice;
				}
				else {
					sTime++;
					queue[0].remain--;
					queue[0].slice--;
					gantt.push_back(table[queue[0].id]);
					
					if (num != 1) {    // RR 
						if (queue[0].slice == 0) {    // Timeout -> change process
							// put current process into the end of the same part of queue 
							queue[0].slice = time_slice;
							Process p = queue.front();
							queue.insert(queue.begin() + num, p);
							queue.erase(queue.begin()) ;
						}
					}					
				}
			}
		}
		
		void HRRN(vector<Process> list, vector<Time> & wt, vector<Time> & tat, vector<string> & gantt) {
			vector<Process> queue;
			
			while (list.size() != 0 || queue.size() != 0) {
				if (queue.size() == 0) {   // no process running
					while (sTime < list[0].arrival) {	
						gantt.push_back("-");
						sTime++;
					}
					queue.push_back(list[0]);
					list.erase(list.begin());
				}
				
				sTime += queue[0].burst;
				while ( sTime >= list[0].arrival && list.size() != 0 ) {
					queue.push_back(list[0]);
					list.erase(list.begin());	 
				} // while
				
				// tat
				Time *ttemp = new Time();
			    tat.push_back(*ttemp);
			    tat[tat.size()-1].command = 5;
			    tat[tat.size()-1].id = queue[0].id;
			    tat[tat.size()-1].time = sTime - queue[0].arrival;
			    
		    	// wt 
				Time *wtemp = new Time();
			    wt.push_back(*wtemp);
			    wt[wt.size()-1].command = 5;
			    wt[wt.size()-1].id = queue[0].id;
			    wt[wt.size()-1].time =  tat[tat.size()-1].time - queue[0].burst;
			    
				// gantt
				for (int i = 0; i < queue[0].burst; i++) 
					gantt.push_back(table[queue[0].id]);
					
				// pop from queue 
				queue.erase(queue.begin()) ;
					
				// sort queue by Response Ratio 
				for (int i = 0; i < queue.size(); i++) 
					queue[i].ratio = (sTime - queue[i].arrival + queue[i].burst) *1000/ queue[i].burst;
				
				for (int i = 0; i < queue.size(); i++) {  // Sorted by Ratio, Arrival Time, PID 
					for (int j = 0; j < queue.size(); j++) {
						if (queue[i].ratio > queue[j].ratio) swap(queue[i], queue[j]);
						else if (queue[i].ratio == queue[j].ratio) {
							if (queue[i].arrival < queue[j].arrival) swap(queue[i], queue[j]);
							else if (queue[i].arrival == queue[j].arrival) {
								if (queue[i].id < queue[j].id) swap(queue[i], queue[j]);
							}
						}
					}
				}
			}
		}
};

int main () {
	int command, time_slice = 0;
	string infilename, outfilename;
	vector<Process> list;
	vector<Time> wt, tat;
	vector<string> gantt; 
	Process p;
	Time t;
	do {
		list.clear();
		wt.clear();
		tat.clear();
		gantt.clear();
		cout << endl << "請輸入檔案名稱:" << endl;
		cin >>  infilename;
		outfilename = "out_" + infilename;
		p.readFile(infilename, list, command, time_slice);
		switch(command) {
			case 0: break;
			case 1:{  // FCFS 
				sTime = 0;
				p.FCFS(list, wt, tat, gantt);
				t.writeFile(outfilename, command, wt, tat, gantt);
				
				break;
			} // case 1 
			case 2:{  // RR 
				sTime = 0;
				p.RR(list, time_slice, wt, tat, gantt);
				t.writeFile(outfilename, command, wt, tat, gantt);
				
				
				break;
			} // case 2 
			case 3:{  // SRTF 
				sTime = 0;
				p.SRTF(list, wt, tat, gantt);
				t.writeFile(outfilename, command, wt, tat, gantt);
				
				break;
			} // case 3 
			case 4:{  // PPRR 
				sTime = 0;
				p.PPRR(list, time_slice, wt, tat, gantt);
				t.writeFile(outfilename, command, wt, tat, gantt);
				
				break;
			} // case 4 
			case 5:{  // HRRN 
				sTime = 0;
				p.HRRN(list, wt, tat, gantt);
				t.writeFile(outfilename, command, wt, tat, gantt);
				
				break;
			} // case 5 
			case 6:{			
				vector<Time> FCFSwt, RRwt, SRTFwt, PPRRwt, HRRNwt;
				vector<Time> FCFStat, RRtat, SRTFtat, PPRRtat, HRRNtat;
				vector<string> FCFSgantt, RRgantt, SRTFgantt, PPRRgantt, HRRNgantt;
				
				sTime = 0;				
				p.FCFS(list, FCFSwt, FCFStat, FCFSgantt);
				sTime = 0;				
				p.RR(list, time_slice, RRwt, RRtat, RRgantt);
				sTime = 0;				
				p.SRTF(list, SRTFwt, SRTFtat, SRTFgantt);
				sTime = 0;				
				p.PPRR(list, time_slice, PPRRwt, PPRRtat, PPRRgantt);
				sTime = 0;				
				p.HRRN(list, HRRNwt, HRRNtat, HRRNgantt);
				t.writeFileAll(outfilename, command, FCFSwt, RRwt, SRTFwt, PPRRwt, HRRNwt, 
								FCFStat, RRtat, SRTFtat, PPRRtat, HRRNtat, 
								FCFSgantt, RRgantt, SRTFgantt, PPRRgantt, HRRNgantt);
				
				break;
			} // case 6 
			default: cout << endl << "Command does not exist!" << endl;
		} // switch*/
		
		list.clear();
		wt.clear();
		tat.clear();
		gantt.clear();
	} while (command != 0);	
		
	system("pause");
	return 0;
}
