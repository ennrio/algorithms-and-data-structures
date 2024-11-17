#include <iostream>
#include <vector>
#include <queue>

class TeamDivider {
public:
    int n;  // Количество студентов
    std::vector<std::vector<int>> friendships; // Матрица знакомств

    TeamDivider(int n, const std::vector<std::vector<int>>& friendships) : n(n), friendships(friendships) {}

    // Метод для поиска минимального количества команд
    int min_teams() {
        std::vector<int> team(n, -1); // Массив для обозначения команды каждого студента
        int team_count = 0;

        for (int i = 0; i < n; ++i) {
            if (team[i] == -1) { // Если студент еще не в команде, создаем новую
                if (!bfs_assign_team(i, team, team_count)) {
                    return -1; // Возвращаем ошибку, если не удается разбить без конфликтов
                }
                team_count++; // Увеличиваем количество команд
            }
        }
        return team_count;
    }

private:
    // Метод BFS для назначения команды студентам в одной компоненте связности
    bool bfs_assign_team(int student, std::vector<int>& team, int current_team) {
        std::queue<int> q;
        q.push(student);
        team[student] = current_team;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int friend_id = 0; friend_id < n; ++friend_id) {
                if (friendships[current][friend_id] == 1) { // Если есть знакомство
                    if (team[friend_id] == -1) { // Если друг еще не в команде
                        team[friend_id] = current_team;
                        q.push(friend_id);
                    }
                    else if (team[friend_id] == current_team) {
                        return false; // Конфликт, если знакомые оказались в одной команде
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    // Пример графа знакомства студентов
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
        std::cout << "Минимальное количество команд: " << min_teams << std::endl;
    }
    else {
        std::cout << "Невозможно разбить студентов на команды без конфликтов" << std::endl;
    }

    return 0;
}