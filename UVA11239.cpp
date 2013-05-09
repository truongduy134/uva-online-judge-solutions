#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>
#include <string>

using namespace std;

#define MAX_LEN_LINE 5000

bool compareProjectAndNumStudentEntry(const pair<string, int> & one, const pair<string, int> & two);

int main(void)
{
	map<string, pair<bool, string> > mapStudentToProject;
	map<string, int> mapProjectToNumStudent;
	char line[MAX_LEN_LINE + 1];
	bool endProgram = false;
	string curProject;
	vector<pair<string, int> > projectAndNumStudentVect;
	map<string, pair<bool, string> >::iterator itStudent;
	map<string, int>::iterator itProject;

	while(1)
	{
		mapStudentToProject.clear();
		mapProjectToNumStudent.clear();

		while(1)
		{
			gets(line);
			if(line[0] == '0')
			{
				endProgram = true;
				break;
			}
			
			if(line[0] == '1')
				break;

			if(islower(line[0]))
			{
				// Map student to the current project
				itStudent = mapStudentToProject.find(line);
				if(itStudent == mapStudentToProject.end())
				{
					// New student
					mapStudentToProject[line] = pair<bool, string>(true, curProject);
				}
				else
				{
					if(itStudent->second.first == true)
					{
						// Still qualified
						if(itStudent->second.second != curProject)
							// Disqualified
							itStudent->second.first = false;	
					}
				}
			}
			else
			{
				curProject = line;
				mapProjectToNumStudent[curProject] = 0;
			}
		}

		if(endProgram)
			break;

		// Go through each qualified student
		for(itStudent = mapStudentToProject.begin(); itStudent != mapStudentToProject.end(); itStudent++)
		{
			if(itStudent->second.first == true)
			{
				itProject = mapProjectToNumStudent.find(itStudent->second.second);
				if(itProject != mapProjectToNumStudent.end())
					(itProject->second)++;
			}
		}

		// Convert the map mapProjectToNumStudent to a vector	
		projectAndNumStudentVect.clear();
		for(itProject = mapProjectToNumStudent.begin(); itProject != mapProjectToNumStudent.end(); itProject++)
		{
			projectAndNumStudentVect.push_back(*itProject);
		}

		sort(projectAndNumStudentVect.begin(), projectAndNumStudentVect.end(), compareProjectAndNumStudentEntry);
		
		for(int ind = 0; ind < (int) projectAndNumStudentVect.size(); ind++)
			printf("%s %d\n", projectAndNumStudentVect[ind].first.c_str(), projectAndNumStudentVect[ind].second);	
	}
	return 0;
}

// A project is sorted first in a decreasing order of the number of student enrolled, then in
// 	a lexicographical order of the project name if there is a tie on the number of students
//	enrolled
bool compareProjectAndNumStudentEntry(const pair<string, int> & one, const pair<string, int> & two)
{
	if(one.second > two.second)
		return true;
	if(one.second < two.second)
		return false;
	return one.first < two.first;
}
