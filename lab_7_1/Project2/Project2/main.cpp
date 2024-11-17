#include <iostream>
#include <vector>
#include <queue>

class TeamDivider {
public:
    int n;  // ���������� ���������
    std::vector<std::vector<int>> friendships; // ������� ���������

    TeamDivider(int n, const std::vector<std::vector<int>>& friendships) : n(n), friendships(friendships) {}

    // ����� ��� ������ ������������ ���������� ������
    int min_teams() {
        std::vector<int> team(n, -1); // ������ ��� ����������� ������� ������� ��������
        int team_count = 0;

        for (int i = 0; i < n; ++i) {
            if (team[i] == -1) { // ���� ������� ��� �� � �������, ������� �����
                if (!bfs_assign_team(i, team, team_count)) {
                    return -1; // ���������� ������, ���� �� ������� ������� ��� ����������
                }
                team_count++; // ����������� ���������� ������
            }
        }
        return team_count;
    }

private:
    // ����� BFS ��� ���������� ������� ��������� � ����� ���������� ���������
    bool bfs_assign_team(int student, std::vector<int>& team, int current_team) {
        std::queue<int> q;
        q.push(student);
        team[student] = current_team;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int friend_id = 0; friend_id < n; ++friend_id) {
                if (friendships[current][friend_id] == 1) { // ���� ���� ����������
                    if (team[friend_id] == -1) { // ���� ���� ��� �� � �������
                        team[friend_id] = current_team;
                        q.push(friend_id);
                    }
                    else if (team[friend_id] == current_team) {
                        return false; // ��������, ���� �������� ��������� � ����� �������
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    // ������ ����� ���������� ���������
    std::vector<std::vector<int>> friendships = {
        {0, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 0}
    };

    int num_students = friendships.size();
    TeamDivider divider(num_students, friendships);

    int min_teams = divider.min_teams();
    if (min_teams != -1) {
        std::cout << "����������� ���������� ������: " << min_teams << std::endl;
    }
    else {
        std::cout << "���������� ������� ��������� �� ������� ��� ����������" << std::endl;
    }

    return 0;
}