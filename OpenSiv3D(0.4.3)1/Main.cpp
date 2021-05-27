
# include <Siv3D.hpp> // OpenSiv3D v0.4.3
using namespace std;

void Main()
{
	Scene::SetBackground(ColorF(0.3, 0.6, 1.0));

	int load = 0;
	double velo = 1;
	pair<double, double> velocity = { 1,1 },circlePos = { 400,300 };
	double color = 0,cv = 0.0025;
	vector<Vec2> track;

	while (System::Update()) {
		ClearPrint();

		//背景の往復する長方形
		for (int i = 0;i < 30;i++) {
			double width = Scene::Time();
			width = width * 100;
			Rect rect = Rect(0, i * 20, 800 - abs((int)(i * 60 - width) % 1601 + 800), 20);
			rect.draw(rect.mouseOver() ? Palette::Green : Palette::Gray);
		}

		//押した跡の円
		if (MouseL.down()) track.push_back(Cursor::Pos());
		if (MouseR.down()&&track.size()>=1) track.pop_back();
		for (auto& i : track) Circle(i, 3).draw(Palette::Lightgrey);

		//座標表示
		Print << U"GUI:" << Cursor::Pos();
		Print << U"Circle:({:.0f},{:.0f})"_fmt(circlePos.first,circlePos.second);
		Print << U"Footprints:" << track.size();

		//繰り返しバウンドする円
		Circle((int)circlePos.first, (int)circlePos.second, 30).draw(ColorF(color));
		if (abs((int)circlePos.first - 400) >= 400) velocity.first *= -1.0;
		if (abs((int)circlePos.second - 300) >= 300) velocity.second *= -1.0;

		circlePos.first += velocity.first;
		circlePos.second += velocity.second;
		
		if (velocity.first < 0) velocity.first = -1 * velo;
		else velocity.first = velo;
		if (velocity.second < 0) velocity.second = -1 * velo;
		else velocity.second = velo;
		
		color += cv;
		cv *= (abs(color - 0.5) >= 0.5 ? -1 : 1);

		//スライダー
		SimpleGUI::Slider(U"Ball speed {:.2f}"_fmt(velo), velo, 0.0, 5.0, Vec2(10, 550), 150, 200);

		//カーソルの円と周囲の円
		Circle(Cursor::Pos(), 20).draw(ColorF(1.0,1.0,1.0,0.5));
		for (int i = 0;i < 12;i++) {
			double t = Scene::Time();
			Vec2 pos = OffsetCircular(Cursor::Pos(), 40, (i*30+t*120)/180*3.14159265);
			Circle(pos, 5).draw();
		}
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
