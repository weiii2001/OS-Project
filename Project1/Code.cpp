#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <unistd.h>
//#include <windows.h>
#include <thread>
#include <pthread.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

vector<int> readFile(string infilename) {
	vector<int> list;
	int num;
	ifstream infile;
	infile.open( infilename.c_str(), ios::in );
	while(!infile) {
		cout << "檔案不存在!!!" << endl;
		cout << endl << "請輸入檔案名稱:" << endl;
		cin >>  infilename;	
		infile.open( infilename.c_str(), ios::in );
	}
	while (infile >> num) {
        list.push_back(num);
    }
	infile.close();
	return list;
}

void writeFile(string outfilename, vector<int> list, double cpu_time) {
	ofstream outfile;
	outfile.open(outfilename.c_str(), ios::out);
	outfile << "Sort:" << endl;
	for (int i = 0; i < list.size(); i++) {
		outfile << list[i] << endl;
	}
	outfile << "CPU Time: " << cpu_time << " (s)" << endl;
	// 基於當前系統的當前日期/時間 
	time_t now = time(0); 
	// 把 now 轉換為字符串形式 
	char* dt = ctime(&now); 
	outfile << "datatime: " << dt << endl; 
	outfile.close();
}

vector<int> cut(vector<int> list, int & now, int & next) {
	vector<int> vec;
	while (now != next) {
		vec.push_back(list[now]);
		now++;
	}
	return vec;
}

void BubbleSort(vector<int> & list) {
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list.size(); j++) {
			if (list[i] < list[j]) swap(list[i], list[j]);
		}
	}
}

class Min {
	public:
		int key;
		int value;
		
		void mergeKArrays(vector<vector<int> > vec, int K, vector<int> & output) {
			int a = 0;
			vector<Min> minheap;
			for (int i = 0; i < K; i++) {
				heapInsert(minheap, i,  vec[i][0]);
				vec[i].erase(vec[i].begin());
			}
			
			while (!minheap.empty()) {
				output.push_back(minheap[0].value);
				a = minheap[0].key;
				if(!vec[a].empty() ) {
					heapInsert(minheap, a, vec[a][0]);
					vec[a].erase(vec[a].begin());
				}
				deleteRoot(minheap);
			}
		}
		void heapInsert(vector<Min> & minheap, int key, int value) {
			Min *temp = new Min() ;
			minheap.push_back( *temp ) ;  // put the new item at the end of heap
			int s = minheap.size() ;
			minheap[s-1].key = key;
			minheap[s-1].value = value ;
			
			int place= s - 1 ;
			int parent= (place-1) /2 ;  // trickle new item up to its position
			
			while( (parent>= 0) && (minheap[place].value < minheap[parent].value ) ){
				swap( minheap[place], minheap[parent] ) ;  // swap items[place] and items[parent]
				place= parent;
				parent= (place-1) /2;
			} // while
		} // heapInsert()
		
		void deleteRoot(vector<Min> & minheap) {
			swap(minheap[0], minheap[minheap.size()-1]);
			minheap.pop_back();
			heapify(minheap, minheap.size(), 0);
		}
		void heapify(vector<Min> & minheap, int n, int i) {
		    int min = i; // Initialize Minimum as root
		    int l = 2 * i + 1; // left = 2*i + 1
		    int r = 2 * i + 2; // right = 2*i + 2
		 
		    // If left child is Smaller than root
		    if (l < n && minheap[l].value < minheap[min].value)
		        min = l;
		 
		    // If right child is Smaller than Minimum so far
		    if (r < n && minheap[r].value < minheap[min].value)
		        min = r;
		 
		    // If Minimum is not root
		    if (min != i) {
		        swap(minheap[i], minheap[min]);
		 
		        // Recursively heapify the affected sub-tree
		        heapify(minheap, n, min);
		    }
		} 

};

int main () {
	int K, command = 0;
	string infilename, outfilename;
	vector<int> list;
	clock_t START,END;
	double cpu_time;
	Min m;
	do {
		cout << "請輸入檔案名稱:" << endl;
		cin >>  infilename;
		cout << endl << "請輸入要切成幾份:" << endl; 
		cin >> K;
		while(K < 0) {
			cout << "輸入格式錯誤!!!" << endl;
			cout << endl << "請輸入要切成幾份:" << endl; 
			cin >> K;  
		}
		cout << endl << "請輸入方法編號:(1, 2, 3, 4)" << endl;
		cin >> command;
		cout << endl;
		
		switch(command) {
			case 0: break;
			case 1:{
				// ************************************cpu time start 
				//START = clock();
        		auto sss = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
				list = readFile(infilename);
				// 直接 Bubble sort 
				BubbleSort(list);
				// ************************************cpu time end
				//END = clock();
		        //cpu_time = ((double) (END - START));
		        auto eee = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			    cpu_time = ((double) (eee - sss));
				outfilename = infilename.substr(0, infilename.size()-4) + "_output1.txt";
				writeFile(outfilename, list, cpu_time/ 1000);
				list.clear();
				
				break;
			} // case 1 
			case 2:{
				// ************************************cpu time start 
				//START = clock();
        		auto sss = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
				list = readFile(infilename);
				vector<vector<int> > vec(K);
				vector<int> output;
				int now = 0, next = 0;
				int part = list.size()/K;
				next = part;
				// 切成 K 分 
				for (int i = 0; i < K; i++) {
					vec[i] = cut(list, now, next);
					now = next;
					next += part;
					if (next > list.size()) next = list.size();
				}
				while (now != next) {
					vec[K-1].push_back(list[now]);
					now++;
				}
				now = 0;
				
				// 先丟 Bubble sort
				for (int i = 0; i < K; i++) {
					BubbleSort(vec[i]);
				}
				// 再丟 Merge 
				m.mergeKArrays(vec, K, output);
				// ************************************cpu time end 
				//END = clock();
		        //cpu_time = ((double) (END - START));
		        auto eee = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			    cpu_time = ((double) (eee - sss));
				outfilename = infilename.substr(0, infilename.size()-4) + "_output2.txt";
				writeFile(outfilename, output, cpu_time/ 1000);
				list.clear();
				vec.clear();
				output.clear();
				
				break;
			} // case 2 
			case 3:{
        		// ************************************cpu time start 
				//START = clock();
        		auto sss = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
				list = readFile(infilename);
				vector<vector<int> > vec(K);     
				int now = 0, next = 0;
				int part = list.size()/K;
				next = part;
				// 切成 K 分 
				for (int i = 0; i < K; i++) {
					vec[i] = cut(list, now, next);
					now = next;
					next += part;
					if (next > list.size()) next = list.size();
				}
				while (now != next) {
					vec[K-1].push_back(list[now]);
					now++;
				}
				now = 0;
        
        		// K Processes run Bubble sort
        
        		string t;
        		for(int i = 0; i < K; i++) {
        			pid_t pid = fork();
        			if (pid < 0) {
			            cout << "Error!!!";
			            exit(-1);
					}
  					else if(pid == 0) {
  						BubbleSort(vec[i]);
			            t = to_string(i) + ".txt";
			            ofstream out;
			            out.open(t.c_str(), ios::out);
	            
			            for(int j = 0; j < vec[i].size(); j++) {
			              out << vec[i][j] << endl;
			            }
			            out.close();
			            exit(0);
 					}
    			}
		        for(int i = 0; i < K; i++) {
		          wait(0);
		        }
		        
			    vec.clear();
	        	int num, j = 0;
				vector<vector<int> > v(K);
        
		        for (int i = 0; i < K; i++) {
		        	t = to_string(i) + ".txt";
		    		  v[i] = readFile(t);
		        }
		        for (int i = 0; i < K; i++) {
		        	t = to_string(i) + ".txt";
		          char *path = const_cast<char*>(t.c_str());
		      		remove(path);
		        }
		        
        		// 再丟 Merge 
				vector<int> output;
				m.mergeKArrays(v, K, output);
				// ************************************cpu time end 
				//END = clock();
		    	//cpu_time = ((double) (END - START));
		    	auto eee = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
				cpu_time = ((double) (eee - sss));
				outfilename = infilename.substr(0, infilename.size()-4) + "_output3.txt";
				writeFile(outfilename, output, cpu_time/ 1000);
				list.clear();
				vec.clear();
        		v.clear();
				output.clear();
				
				break;
			} // case 3 
			case 4:{
				// ************************************cpu time start 
				//START = clock();
		        auto sss = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
				list = readFile(infilename);
				vector<vector<int> > vec(K);
				vector<int> output;
				int now = 0, next = 0;
				int part = list.size()/K;
				next = part;
				// 切成 K 分 
				for (int i = 0; i < K; i++) {
					vec[i] = cut(list, now, next);
					now = next;
					next += part;
					if (next > list.size()) next = list.size();
				}
				while (now != next) {
					vec[K-1].push_back(list[now]);
					now++;
				}
				now = 0;
				
				// K Threads run Bubble sort
				vector<thread> threads;
				for (int i = 0; i < K; i++) {
			        threads.push_back(thread(BubbleSort, ref(vec[i])));
        		}
			    for (int i = 0; i < K; i++) 
			        threads[i].join();
			    
			    threads.clear();
			    
				// 再丟 Merge 
				m.mergeKArrays(vec, K, output);
				// ************************************cpu time end 
				//END = clock();
		        //cpu_time = ((double) (END - START));
		        auto eee = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			    cpu_time = ((double) (eee - sss));
				outfilename = infilename.substr(0, infilename.size()-4) + "_output4.txt";
				writeFile(outfilename, output, cpu_time/ 1000);
				list.clear();
				vec.clear();
				output.clear();
				
				break;
			} // case 4 
			default: cout << endl << "Command does not exist!" << endl;
		} // switch
	} while (command != 0);	
		
	system("pause");
	return 0;
}
