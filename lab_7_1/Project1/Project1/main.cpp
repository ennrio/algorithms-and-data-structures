#include<iostream>
#include<vector>

class Cords {
public:
	int x;
	int y;
	Cords(int x, int y) :x(x), y(y) {
	}
};

// добавл€ет коодинаты игрока в двумерный массив, где кажда€ €чейка означает команду
void push_player(std::vector<std::vector<Cords>>& commands, std::vector<std::vector<int>> matrix, const int x, const int y, int& count_commands) {
	bool is_push = false;
	for (int i = 0; i < count_commands; i++) {
		bool flag = true;
		for (int j = 0; j < commands[i].size(); j++) {
			if ((x == commands[i][j].y || y == commands[i][j].x )) {
				flag = false;
				//|| (x == commands[i][j].x || y == commands[i][j].y)
				// break;
			}
		}
		if (flag) {
			commands[i].push_back(Cords(x, y));
			is_push = true;
			break;
		}
	}
	if (!is_push) {
		count_commands++;
		commands.push_back({ Cords(x, y) });
	}
}


void print_commands(const std::vector<std::vector<Cords>>& commands) {
	for (int i = 0; i < commands.size(); i++) {
		for (int j = 0; j < commands[i].size(); j++) {
			std::cout << commands[i][j].x << "  " << commands[i][j].y << "\t";
		}
		std::cout << std::endl;
	}
}

// ¬ сз€ви с несовершенством алгоритма при переборе одна и та же точка может добавитьс€ 2 и более раза, в зависимости от колличества маршрутов,
// идущих в неЄ
void delete_duplicate(std::vector<std::vector<Cords>>& commands) {
	for (auto& command : commands) {
		if (command.size() >= 2) {
			for (size_t j = 0; j < command.size(); ++j) {
				for (size_t k = j + 1; k < command.size(); ++k) {
					if (command[j].x == command[k].x) {
						// || command[j].y == command[k].y
						command.erase(command.begin() + k);
						--k;
					}
				}
			}
		}
		else {
			continue;
		}

	}
}

// ѕровер€ет есть ли в массиве игроков точка с такой же кординатой <Ќужна дл€ balace>
bool check_duplicate(Cords point, std::vector<std::vector<Cords>> commands,int number_command) {
	auto command = commands[number_command];
	for (size_t i = 0; i < command.size(); i++) {
		if (command[i].x == point.y || command[i].y == point.x) {
			return true;
		}
	}
	return false;
}

//¬озвращает номер самой маленькой команды
int litle_command(const std::vector<std::vector<Cords>>& commands) {
	int min_index = 0;
	for (int i = 1; i < commands.size(); i++) {
		if (commands[i].size() < commands[min_index].size()) {
			min_index = i;
		}
	}
	return min_index;
}
//¬озвращает номер самой большой команды
int big_command(const std::vector<std::vector<Cords>>& commands) {
	int max_index = 0;
	for (int i = 1; i < commands.size(); i++) {
		if (commands[i].size() > commands[max_index].size()) {
			max_index = i;
		}
	}
	return max_index;
}

//ѕровер€ет соответсвует ли разбиение массива условию
bool check_balance(std::vector<std::vector<Cords>> commands) {
	//std::cout << "dflsk  " << commands[litle_command(commands)].size() << "  " << commands[big_command(commands)].size() << std::endl;
	if (commands[litle_command(commands)].size() <= commands[big_command(commands)].size() / 2) {
		return false;
	}
	else {
		return true;
	}
}

//ѕодгон€ет под условие массив с игроками
void balance(std::vector<std::vector<Cords>>& commands,int& count_commands) {
	int i = 0;
	while (!check_balance(commands)) {
		int number_big_command = big_command(commands);
		int number_litle_command = litle_command(commands);
		for (auto point = commands[number_big_command].begin(); point != commands[number_big_command].end();) {
			if (i > 30) {
				commands.push_back({Cords(point->x,point->y)});
				point = commands[number_big_command].erase(point);
				i = 0;
			}
			if (!check_duplicate(*point, commands, number_litle_command)) {
				commands[number_litle_command].push_back(*point);
				point = commands[number_big_command].erase(point);
				break;
			}
			else {
				point++;
			}
		}
		i++;
	}
}


int end_function(std::vector<std::vector<int>> matrix) {
	std::vector<std::vector<Cords>> commands;
	int count_commands = 0;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] == 1) {
				push_player(commands, matrix, i, j, count_commands);
			}
		}
	}
	for (int i = 0; i < count_commands; i++) {
		for (int j = 0; j < commands[i].size(); j++) {
			std::cout << commands[i][j].x << "\t" << commands[i][j].y << std::endl;
		}
		std::cout << std::endl;
	}
	//std::cout<< "ƒо balance";

	balance(commands, count_commands);
	//for (int i = 0; i < count_commands; i++) {
	//	for (int j = 0; j < commands[i].size(); j++) {
	//		std::cout << commands[i][j].x << "\t" << commands[i][j].y << std::endl;
	//	}
	//	std::cout << std::endl;
	//}
	return commands.size();
}

bool check_split(int num,std::vector<std::vector<int>> matrix) {
	return (num - end_function(matrix) >= 0) && (matrix.size() >= num);
}

void change_matrix(std::vector<std::vector<int>> &matrix1) {
	std::vector<std::vector<int>> matrix2(matrix1[0].size(), std::vector<int>(matrix1[0].size(), 0));
	for (int i = 0; i < matrix1.size(); i++) {
		int a = -1;
		int b = 0;
		for (int j = 0; j < matrix1[0].size(); j++) {
			if (a == -1 && matrix1[i][j] == 1) {
				a = j;
				continue;
			}
			else if (a != -1 && matrix1[i][j] == 1 && b==0){
				b = j;
			}
		}
		matrix2[a][b] = 1;
		matrix2[b][a] = 1;
	}
	matrix1.clear();
	matrix1 = matrix2;

}

int main() {
	setlocale(LC_ALL, "RU");

	/*
	std::vector<std::vector<int>> matrix1 = {
		{1,1,0,0,0,0},
		{0,1,0,1,0,0},
		{0,1,1,0,0,0},
		{0,0,1,1,0,0},
		{0,0,0,1,1,0},
		{0,0,0,0,1,1}
	};

	change_matrix(matrix1);
	for (int i = 0; i < matrix1.size(); i++) {
		for (int j = 0; j < matrix1[i].size(); j++) {
			std::cout << matrix1[i][j];
		}
		std::cout<<std::endl;
	}
	*/



	/*


	std::vector<std::vector<int>> matrix;
	matrix = {
		{0,1,0,0,0,0,0},
		{1,0,1,1,0,0,0},
		{0,1,0,1,0,0,0},
		{0,1,1,0,1,0,0},
		{0,0,0,1,0,1,0},
		{0,0,0,0,1,0,0},
		{0,0,0,0,0,0,1}
	};

	std::vector<std::vector<int>> matrix2;
	matrix2 = {
		{0,1,0,0,0,0,0},
		{1,0,1,1,1,0,0},
		{0,1,0,1,0,0,0},
		{0,1,1,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,0,0,0,0,0,1},
		{0,0,0,0,0,1,0}
	};

	std::vector<std::vector<int>> matrix3;
	matrix3 = {
		{0,1,0,0,0,0,0},
		{1,0,1,1,1,0,0},
		{0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,0,0,0,0,0,1},
		{0,0,0,0,0,1,0}
	};

	std::vector<std::vector<int>> matrix4;
	matrix4 = {
		{0,1,0},
		{1,0,1},
		{0,1,0}
	};

	std::cout<<end_function(matrix4) << std::endl;
	std::cout << check_split(3, matrix4);

	*/

	/*
	while (true)
	{
		int q;
		std::cout << "¬ведите кол-во рЄбер>>";
		std::cin >> q;
		int p;
		std::cout << "¬ведите кол-во точек>>";
		std::cin >> p;
		std::vector<std::vector<int>> matrix(q, std::vector<int>(p, 0));
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < p; j++) {
				int num;
				std::cout << "введите " <<i <<"-ый " << j <<"-ый элемент массива >> ";
				std::cin >> num;
				matrix[i][j] = num;
			}
		}
		change_matrix(matrix);
		std::cout << "минимально возможное колличество команд - " << end_function(matrix) << std::endl;
		std::cout << "1 - узнать возможно заданное колличество комманд" << std::endl;
		std::cout << "2 - задать новую матрицу" << std::endl;
		std::cout << "3 - выйти" << std::endl;
		int n;
		std::cin >> n;
		if (n == 1) {
			int count;
			std::cout << "задайте колличество команд>>";
			std::cin >> count;
			if (check_split(count,matrix)) {
				std::cout << "разбиение возможно" << std::endl;
			}
			else {
				std::cout << "разбиение невозможно" << std::endl;
			}
		}
		else if (n == 2) {
			continue;
		}
		else {
			break;
		}

	}

	return 0;
}
*/

	std::vector<std::vector<int>> matrix;
	matrix = {
		{1,1,0,0,0,0},
		{0,1,0,1,0,0},
		{0,1,1,0,0,0},
		{0,0,1,1,0,0},
		{0,0,0,1,1,0},
		{0,0,0,0,1,1}
	};
	change_matrix(matrix);
	std::vector<std::vector<Cords>> commands;
	int count_commands = 0;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] == 1) {
				push_player(commands, matrix, i, j, count_commands);
			}
		}
	}
	print_commands(commands);
	delete_duplicate(commands);
	std::cout << std::endl;
	print_commands(commands);
	//std::cout << "дубликат - " << check_duplicate(Cords(2, 8), commands, 0) << std::endl;
	std::cout << litle_command(commands) << std::endl;
	std::cout << big_command(commands) << std::endl;
	balance(commands, count_commands);
	std::cout << std::endl;
	std::cout << "dslfkds - " << end_function(matrix) << std::endl;
	print_commands(commands);
}