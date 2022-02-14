#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <windowsx.h>
#include <cstdlib>
#include <stdio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <WinUser.h>

using namespace std;

struct meeting {
    string name;
    string link;
    int number_of_days_in_week;
    int days_of_the_week[7];
    int hour;
    int minut;
};


int is_before(meeting meet1, meeting meet2) {
    if (meet1.hour < meet2.hour || (meet1.hour == meet2.hour && meet1.minut <= meet2.minut)) {
        return 1;
    }
    return 0;
}

int get_number_of_day(const char* day_in_letters){
    char first_char = *day_in_letters;
    char second_char = *(day_in_letters+1);
    switch (first_char) {
    case 'S':
        if (second_char == 'u'){
            return 1;
        }
        if (second_char == 'a') {
            return 0;
        }
        break;
    case 'M':
        return 2;
        break;
    case 'T':
        if (second_char == 'u'){
            return 3;
        }
        if (second_char == 'h') {
            return 6;
        }
        break;
    case 'W':
        return 5;
    case 'F':
        return 7;
    default:
        return -1;
    }
    return -1;

}

meeting all_meetings[31];
int number_of_meetings = 0;

void initialize_all_meetings() {
    string text_of_file;
    int number_of_meeting_to_save = 0;
    int number_of_days;
    stringstream number_of_days_str;
    int day;
    ifstream data_file("C:/ProgramData/TeymooriAnar/AutoMeet/ListOfMeetings.txt");
    while (getline(data_file, text_of_file)) {
        meeting meet;
        meet.name = text_of_file;
        getline(data_file, text_of_file);
        meet.link = text_of_file;
        getline(data_file, text_of_file);
        stringstream number_of_days_str(text_of_file);
        number_of_days_str >> number_of_days;
        meet.number_of_days_in_week = number_of_days;
        while (number_of_days > 0) {
            getline(data_file, text_of_file);
            stringstream number_of_days_str(text_of_file);
            number_of_days_str >> day;
            meet.days_of_the_week[meet.number_of_days_in_week-number_of_days] = day;
            number_of_days --;
        }
        getline(data_file, text_of_file);
        stringstream number_of_hour_str(text_of_file);
        number_of_hour_str >> day;
        meet.hour = day;

        getline(data_file, text_of_file);
        stringstream number_of_min_str(text_of_file);
        number_of_min_str >> day;
        meet.minut = day;
        all_meetings[number_of_meetings] = meet;
        number_of_meetings ++;

    }
     data_file.close();
}

int is_for_today(meeting meet, int today_int) {
    for (int i=0; i<meet.number_of_days_in_week; i++) {
        if (meet.days_of_the_week[i] == today_int) {
            return 1;
        }
    }
    return 0;
}

int main() {
    system("title AutoMeet(BackgroundService)");
    initialize_all_meetings();

	ShowWindow( GetConsoleWindow(), SW_HIDE );

    time_t now;
    char* dt;
    int today_number;
    meeting meet;
    int opened;
    int is_any_upcoming;
    int next_meet_set = 0;
    meeting next_meet;
    int to_wait;
    while (1) {
        now = time(0);
        opened = 0;

        dt = ctime(&now);
        tm *ltm = localtime(&now);

        today_number = get_number_of_day(dt);
        is_any_upcoming = 0;
        for (int i = 0; i < number_of_meetings; i++) {
            meet = all_meetings[i];
            if (is_for_today(meet, today_number) == 1) {


                if (meet.hour > ltm->tm_hour || (meet.hour == ltm->tm_hour && meet.minut > ltm->tm_min)){
                    cout << "There is an upcoming meeting for today : " << meet.name << "\tat time\t" << meet.hour << ":" << meet.minut << endl;
                    if(next_meet_set == 0) {
                        next_meet = meet;
                        next_meet_set = 1;
                    } else {
                        if (is_before(meet, next_meet)) {
                            next_meet = meet;
                        }
                    }
                    is_any_upcoming = 1;
                }

                if ((ltm->tm_hour == meet.hour && ltm->tm_min <= meet.minut && ltm->tm_min >= meet.minut - 30)||(ltm->tm_hour == meet.hour - 1 && ltm->tm_min-30>=meet.minut)) {
                    string command = "start "+meet.link;
                    const char * command_char_ptr = command.c_str();
                    cout << "Opening meeting "<<meet.name<<" for time "<<meet.hour<<":"<<meet.minut<<" ... "<<endl;
                    system(command_char_ptr);
                    Sleep(30*60000);
                    opened = 1;
                }
            }

        }
        if (is_any_upcoming == 0) {
            cout << "There is not any opcoming meeting today! GoodLuck!" << endl;
        }

        cout << "Last time checked at: " << dt << endl;
        Sleep(180000);
        system("cls");
    }


}
