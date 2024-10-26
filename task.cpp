#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Student
{
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

struct Group
{
    string Id;
    vector<Student> Students;
};

Student anna = {
        "Anna",
        "G1",
        {4, 5, 5, 5},
        {"Geom", "Math", "Rus", "History"}
};
Student ivan = {
        "Ivan",
        "G2",
        {4, 5, 5, 3},
        {"Geom", "Math", "Rus", "History"}
};
Student petr = {
        "Petr",
        "G1",
        {2, 3, 4, 5},
        {"Geom", "Math", "Rus", "History"}
};
Student masha = {
        "Maria",
        "G3",
        {4, 4, 5, 4},
        {"Geom", "Math", "Rus", "History"}
};
Student dima = {
        "Dmitry",
        "G3",
        {5, 5, 5, 5},
        {"Geom", "Math", "Rus", "History"}
};

void SortByName(vector<Student>& students){
    for (int i = 0; i < (students.size()); i++){
        for (int j = i; j < (students.size()); j++){
            if (students[i].Name > students[j].Name){
                Student b = students[i];
                students[i] = students[j];
                students[j] = b;
            }
        }
    }
}
unsigned sum(vector<unsigned> vec){
    unsigned res = 0;
    for(unsigned i: vec)
        res += i;
    return res;
}
void SortByRating(vector<Student>& students){
    for (int i = 0; i < (students.size()); i++){
        for (int j = i; j < (students.size()); j++){
            double rate_i = (double) (sum(students[i].Ratings)  / students[i].Ratings.size());
            double rate_j = (double) (sum(students[j].Ratings)  / students[j].Ratings.size());
            if (rate_i > rate_j){
                Student b = students[i];
                students[i] = students[j];
                students[j] = b;
            }
        }
    }
}

size_t CountTwoness(const vector<Student>& students){
    size_t res = 0;
    for (const Student & student : students)
        for (unsigned j: student.Ratings)
            if (j == 2){
                res += 1;
                break;
            }
    return res;
}

size_t CountExcellent(const vector<Student>& students){
    size_t res = 0;
    for (const Student & student : students){
        int prom = 0;
        for (unsigned j: student.Ratings)
            if (j == 5)
                prom += 1;
        if (prom == student.Ratings.size())
            res += 1;
    }
    return res;
}

vector<Student> VectorMathExcellent(const vector<Student>& students){
    vector<Student> res;
    for (const Student & student : students){
        int n = 0;
        for (; n < student.Subjects.size(); n++)
            if (student.Subjects[n] == "Math")
                break;
        if (student.Ratings[n] == 5)
            res.push_back(student);
    }
    return res;
}

vector<string> GroupsId(const vector<Student>& students){
    vector<string> res;
    for (const Student & student : students){
        if (find(res.begin(), res.end(), student.GroupId) == res.end())
            res.push_back(student.GroupId);
    }
    return res;
}

vector<Group> Groups(const vector<Student>& students){
    vector<string> groups = GroupsId(students);
    vector<Group> res;
    for (string group: groups){

        vector<Student> S;
        for (Student stud: students){
            if (stud.GroupId == group)
                S.push_back(stud);
        }
        Group g = {
                group,
                S
        };
        res.push_back(g);
    }
    return res;
}

void vyvod(vector<Student>& students){
    for (Student i: students)
        cout << i.Name << " ";
    cout << endl;
}
int main(){
    vector<Student> students = {ivan, anna, petr, masha, dima};
    SortByName(students);
    vyvod(students);
    SortByRating(students);
    vyvod(students);
    cout << CountTwoness(students) << endl;
    cout << CountExcellent(students) << endl;
    vector<Student> exMath = VectorMathExcellent(students);
    vyvod(exMath);
    vector<string> groups = GroupsId(students);
    for (string i: groups)
        cout << i << " ";
    cout << endl;
    vector<Group> g = Groups(students);
    for (Group i: g){
        cout << i.Id << ": ";
        for (Student st: i.Students)
            cout << st.Name << " ";
        cout << endl;
    }

}
