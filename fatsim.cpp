// Kareem Abdelaty
//30075331	

#include "fatsim.h"
#include <cstdio>
#include <unordered_map>
#include <stack>
#include <utility>


// reimplement this function
void fat_sim(const std::vector<long> & fat, long & longest_file_blocks, long & unused_blocks)
{
  longest_file_blocks = 0;
  unused_blocks = 0;
  //as each node has an out degree of one we can remember the paths so we dont have to follow them again
  //pair that stores length and if it ends in negative one
  //index is current node, nextNode is next Node
  std::unordered_map<int,std::pair<long,int>> savedPaths;
  std::unordered_map<int,int> unused;
  for(unsigned int i =0; i<fat.size();i++){
	  unsigned int index = i;
	  std::unordered_map<long,int> seen;
	  std::stack<int> s;
	  bool done  = false;
	  while(1){
		long nextNode = fat[index];
		if(!(savedPaths.find(nextNode) == savedPaths.end())){
			unsigned long int j = s.size();
			for(unsigned long int x =0 ; x<=j ; x++){
				savedPaths[index] = savedPaths[nextNode];
				savedPaths[index].first+=1;
				if(savedPaths[index].second == -1){
					if(savedPaths[index].first > longest_file_blocks){
						longest_file_blocks = savedPaths[index].first;
					}
				}else{
					if(unused.find(index)==unused.end()){
						unused_blocks++;
						unused[index] =1;
					}
				}
				if(x == j){
					break;
				}
				nextNode = index;
				index = s.top();
				s.pop();
					
			}
			break;
		}
		if(nextNode == -1){
			std::pair <long,int> x(0,-1);
			savedPaths[nextNode] = x;
			done = true;
			continue;
		}else if(!(seen.find(nextNode) == seen.end())){
			std::pair <long,int> x(0,nextNode);
			savedPaths[nextNode] = x;
			done = true;
			continue;
		}
		if(!done){
			s.push(index);
			seen[index] = 1;		
		}
		index = nextNode;
	  }
  }
  
}
