#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int,int>;

const int M = 10E8+10;
int main() {
    int n, k; cin>>n>>k;
    
    vector<int> L(n), R(n);
    for (int i=0; i<n; ++i) cin>>L[i];
    for (int i=0; i<n; ++i) cin>>R[i];
    
    vector<pii> courses(n);
    for (int i=0; i<n; ++i) {
        courses[i] = {R[i], L[i]};
    }
    
    // Sort courses by their ending times
    sort(courses.begin(), courses.end());

    //print the courses
    //for (const auto& elem : courses) {
    //    cout << "{" << elem.second << ", " << elem.first << "}" << endl;
    //}

    //紀錄k個人排課的end
    vector<int> tails;
    
    //cout<<"Selected courses: "<<endl;
    int cnt = 0;
    //second = start time, first = end time
    for (const auto &now : courses) {
        if (tails.size() < k)
        {
            if(tails.empty()) 
            {
                tails.push_back(now.first); 
                cnt++;
                //cout << "{" << now.second << ", " << now.first << "}" << endl;
                
            }
            else
            {
                bool now_plug_in = false;
                vector<int> diff2(tails.size()); 
                for(int i=0; i<tails.size(); i++)
                {
                    diff2[i] = now.second - tails[i];
                    if(diff2[i] <= 0) diff2[i] = M;//避免diff <= 0的情況
                }
                //for(int i=0; i<k; i++) cout<<abs_diff2[i]<<' ';
                //find the index with min. diff between now.start and tails
                auto minIt2 = min_element(diff2.begin(), diff2.end());
                int minIndex2 = distance(diff2.begin(), minIt2);
                //cout<<"minIndex = "<<minIndex2<<endl;
                if(diff2[minIndex2] > 0 && diff2[minIndex2] != M)
                {
                    tails[minIndex2] = now.first;
                    //cout << "{" << now.second << ", " << now.first << "}" << endl;
                    cnt ++;
                    now_plug_in == true;
                }
                else if(now_plug_in == false)
                {
                    tails.push_back(now.first);
                    cnt++;
                    //cout << "{" << now.second << ", " << now.first << "}" << endl;
                }
            }
            
            
        } 
        else
        {   
            //diff[i] = now.start - tails[i]
            vector<int> diff(k); 
            for(int i=0; i<k; i++)
            {
                diff[i] = now.second - tails[i];
                if(diff[i] <= 0) diff[i] = M;//避免diff <= 0的情況
            }
            vector<int> abs_diff(k,M); 
            for(int i=0; i<k; i++) abs_diff[i] = abs(diff[i]);

            //find the index with min. diff between now.start and tails
            auto minIt = min_element(abs_diff.begin(), abs_diff.end());
            int minIndex = distance(abs_diff.begin(), minIt);
            //cout<<"minIndex = "<<minIndex<<endl;
            if(diff[minIndex] != M)
            {
                tails[minIndex] = now.first;
                //cout << "{" << now.second << ", " << now.first << "}" << endl;
                cnt ++;
            }

        }
    }
    cout << cnt << endl;
}