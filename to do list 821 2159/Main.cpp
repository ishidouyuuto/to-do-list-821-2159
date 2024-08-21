#include<Siv3D.hpp>

class To_do {
private:
	Array<String> musttodo;
	bool scoreIncremented = false;
	bool titleInitialized = false;
	Array<TextEditState> textEdits;// テキストボックスの状態を保持
	bool scoreCheck = false;



public:
	enum class Page {
		Title,
		Game,
		Settings,
		Score
	};


	Page currentPage = Page::Title;
	String name;
	int score = 0;
	int scoreTotal = 0;
	String task;

	bool check = false;
	Array<int> scores;
	bool check0 = false;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	bool chec = false;

	To_do() {
		textEdits.emplace_back();  // 初期状態で1つのTextBoxを追加
	}

	void systemstart() {
		Print << U"Hello, ";
		Console.open();
		std::cin >> name;

		this->name = name;
		Print << this->name;
		Stopwatch stopwatch{ StartImmediately::Yes };
		while (System::Update()) {
			if (3s <= stopwatch) {
				ClearPrint();
				break;
			}
		}
	}

	void InPut() {
		for (size_t i = 0; i < textEdits.size(); ++i) {
			SimpleGUI::TextBox(textEdits[i], Vec2{ 100, 140 + static_cast<int>(i) * 40 });
		}

		// ボタンを押した時にTextBoxを追加する
		if (SimpleGUI::Button(U"Add Task", Vec2{ 320, 140 + static_cast<int>(textEdits.size()) * 40 })) {
			textEdits.emplace_back();  // 新しいTextBoxを追加
		}

		// 3キーが押された時にタスクを保存する
		if (Key3.down()) {
			for (const auto& textEdit : textEdits) {
				musttodo.push_back(textEdit.text);  // 各TextBoxの内容を保存
			}
		}

		// Clear Allボタンを押した時にTextBoxをクリアする
		if (SimpleGUI::Button(U"Clear All", Vec2{ 320, 200 + static_cast<int>(textEdits.size()) * 40 })) {
			textEdits.clear();  // 全てのTextBoxをクリア
			textEdits.emplace_back();  // 最初のTextBoxを追加
		}
	}



	void Checktasks() {
		static Array<bool> checks(musttodo.size(), false);

		if (checks.size() != musttodo.size()) {
			checks.resize(musttodo.size(), false);
		}

		for (size_t i = 0; i < musttodo.size(); i++) {
			SimpleGUI::CheckBox(checks[i], musttodo[i], Vec2{ 100, 40 + i * 40 });
		}

		// スコアのリセット用
		bool anyChecked = false;

		for (size_t i = 0; i < checks.size(); i++) {
			if (checks[i]) {
				anyChecked = true;
				if (!scoreIncremented) {
					score++;
					scoreIncremented = true;
				}
			}
		}

		if (!anyChecked) {
			scoreIncremented = false;  // タスクがチェックされていなければ、スコアの加算をリセット
		}
	}


	void CheckScore() {
		if (!scoreCheck) {
			Print << score;
			scoreCheck = true;

		}
	}
	void Backboard() {
		const double hue = (Scene::Time() * 60);
		Scene::SetBackground(HSV{ hue, 0.6, 1.0 });


		switch (currentPage) {

		case Page::Title:
			FontAsset(U"TitleFont")(U"Title Screen").drawAt(Scene::Center(), Palette::Black);
			if (!titleInitialized) {
				systemstart();
				titleInitialized = true;
			}
			if (SimpleGUI::Button(U"Checktasks", Vec2{ 400, 400 })) {
				currentPage = Page::Game;
			}

			if (SimpleGUI::Button(U"InPut", Vec2{ 400, 460 })) {
				currentPage = Page::Settings;
			}
			if (SimpleGUI::Button(U"Check Score", Vec2{ 400, 520 })) {
				currentPage = Page::Score;
			}
			break;

		case Page::Game:
			FontAsset(U"TitleFont")(U"Game Screen").drawAt(Scene::CenterF(), Palette::Black);
			Checktasks();

			if (SimpleGUI::Button(U"Back to Title", Vec2{ 400, 400 })) {
				currentPage = Page::Title;
			}
			if (SimpleGUI::Button(U"InPut", Vec2{ 400, 460 })) {
				currentPage = Page::Settings;
			}
			if (SimpleGUI::Button(U"Check Score", Vec2{ 400, 520 })) {
				currentPage = Page::Score;
			}
			break;

		case Page::Settings:
			FontAsset(U"TitleFont")(U"Settings Screen").drawAt(Scene::CenterF(), Palette::Black);
			InPut();

			if (SimpleGUI::Button(U"Back to Title", Vec2{ 400, 400 })) {
				currentPage = Page::Title;
			}
			if (SimpleGUI::Button(U"Check tasks", Vec2{ 400, 460 })) {
				currentPage = Page::Game;
			}
			if (SimpleGUI::Button(U"Check Score", Vec2{ 400, 520 })) {
				currentPage = Page::Score;
			}
			break;

		case Page::Score:
			FontAsset(U"Titelfont")(U"Settings Screen").drawAt(Scene::CenterF(), Palette::Black);
			CheckScore();
			if (SimpleGUI::Button(U"Back to Title", Vec2{ 400, 400 })) {
				currentPage = Page::Title;
			}
			if (SimpleGUI::Button(U"Check tasks", Vec2{ 400, 460 })) {
				currentPage = Page::Game;
			}
			if (SimpleGUI::Button(U"InPut", Vec2{ 400, 520 })) {
				currentPage = Page::Settings;
			}
			break;
		}
	}
};

void Main() {
	To_do to_do;

	while (System::Update()) {
		to_do.Backboard();
	}
}
