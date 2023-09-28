# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::Silver);

	const Audio bad{ U"example/blip04.mp3" };
	const Audio answer{ U"example/correct_answer1.mp3" };
	const Audio answer10{ U"example/correct_answer2.mp3" };
	const Audio answer25{ U"example/correct_answer3.mp3" };
	// オーディオを再生

	const Texture texture{ U"example/SCP-Logo-2400.png" };
	
	String a;
	int score = 0;

	// 問題文のリスト
	const Array<Array<String>> texts =
	{
		{
			U"SCP-682 - [不死身の爬虫類]",//問題文
			U"hujiminohatyuurui",//ローマ字文字列
			U"-…奴らは…忌まわしい…",
		},
		{
			U"SCP-1287 - [かなしまないで]",
			U"kanasimanaide",
			U"-私は、私にできることをした",
		},
		{
			U"SCP-1983 - [先の無い扉]",
			U"sakinonaitobira",
			U"-幸運を。死にゆく者より敬礼を。",
		},
		{
			U"SCP-062-JP - [生存権]",
			U"seizonkenn",
			U"-上告します。",
		},
	    {
			U"SCP-544-JP - [孤独な放送室]",
			U"kodokunahousousitu",
			U"-よう、お嬢ちゃん。",
		},
	    {
			U"SCP-8900-EX - [青い、青い空]",
			U"aoi,aoisora",
			U"-諸君、我々は失敗した。",
		},
		{
			U"SCP-548-JP - [歌う雨音]",
			U"utauamaoto",
			U"-盛大な拍手で、お見送りください。",
		},
		{
			U"確保、収容、保護。",
			U"kakuho,syuuyou,hogo.",
			U"-SCP財団の基本理念",
		},
		{
			U"安定した継続的収容が可能なオブジェクト。",
			U"safe",
			U"-オブジェクトクラス",
		},
		{
			U"常に収容違反が警戒されるオブジェクト。",
			U"euclid",
			U"-オブジェクトクラス",
		},
		{
			U"収容が困難あるいは不可能なオブジェクト。",
			U"keter",
			U"-オブジェクトクラス",
		},
		
	};


	// 問題文をランダムに選ぶ
	Array<String> target = texts.choice();

	// 入力中の文字列
	String input;

	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	while (System::Update())
	{
		texture.drawAt(125, 490);

		if (KeyControl.down())
		{
			target = texts.choice();
		}
		if (KeyPageUp.down())
		{
			score++;
		}
		if (KeyPageDown.down())
		{
			score--;
		}


		// テキスト入力（TextInputMode::DenyControl: エンターやタブ、バックスペースは受け付けない）
		TextInput::UpdateText(input, TextInputMode::DenyControl);

		// 誤った入力が含まれていたら削除する
		while (not target[1].starts_with(input))
		{
			bad.play();
			input.pop_back();
		}

		// 一致したら次の問題へ移る
		if (input == target[1])
		{
			
			
			// 問題文配列をランダムに選ぶ
			target = texts.choice();
				// 入力文字列をクリアする	
				input.clear();
				score++;
			if (score == 5) {
				a = U"Good";
				answer10.play();
			}
			else if (score == 25) {
				a = U"Excellent";
				answer25.play();
			}
			else {
				a.clear();
				answer.play();
			}
		}

		// 問題文を描画する
		font(target[0]).draw(30, Vec2{ 40, 40 }, ColorF{ 0.98 });
		font(target[1]).draw(40, Vec2{ 40, 80 }, ColorF{ 0.98 });
		font(target[2]).draw(30, Vec2{315, 550}, ColorF{0.5});

		// 入力中の文字を描画する
		font(input).draw(40, Vec2{ 40, 80 }, ColorF{ 0.12 });

		font(U"収容数：").draw(40, Vec2{40, 150}, ColorF{0.98});
		font(score).draw(40, Vec2{ 240, 150 }, ColorF{ 0.98 });

		font(a).draw(40, Vec2{ 320,200 }, Palette::Gold);
	}
}
