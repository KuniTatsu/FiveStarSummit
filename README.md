# FiveSterSummit
***操作説明***

Left,RightArrow:カード選択移動 使う予定のカードを移動する。

Enter:カード使用    選択中のカードを使用する。

***カード(右下にある5この白い四角について）***

日数を進めるためのカード。左上にある数字の分だけ、画面左上のすごろくが進む。

イベントID0,1はステータスの上がり幅が異なるだけなので割愛。

イベントID2のカードは確率でアビリティを付与する。

***すごろくについて(上のカラフルな四角について)***

カードで選択された日数分進むすごろく。

プレイヤーの位置は常に左から3番目で固定。

すごろくのマスにもイベントが振られており、

青：ステータス上昇

赤：ステータス減少

黃：スキル獲得（未実装）

白：ランダムに上昇と減少


となる。


***流れ***
//入学式実装につきデバッグコマンドを廃止した

//spaceキーでキャラ作成(何体か作っておくとDebugしやすい)

カード選択画面
↓

Left,RightArrowでカードを移動。選択中カードが少し上に頭が出る

//キーパッド0キーで選択実行。

enterキーで選択実行
↓

数字分移動したらイベントwindowがでるのでEnterを2回押すと

カードとすごろくますのイベントが実行され、ステータスが変化する。

***個人訓練内容選択について***

Escキーを押下でメニューが出現

上から二番目を選択中にEnter

キャラ一覧の右側にあるボタン(選択中:〇〇)をクリック

更に右側に訓練一覧が出るのでup,downArrowキーで移動、Enterで選択

訓練ごとに上がる能力値がかわる。(おまかせはランダム)

//今後の実装予定

おまかせは全能力値がおなじになるように実装

個人訓練で上がる能力値をどこかで説明表示

**セーブロードについて**

未実装。

実装の際は現在のすごろくセルのイベントIDとカードのイベントID,経過日数,在籍キャラクターを外部出力するように実装する。

なお現在はゲーム中からタイトルに戻ると例外処理が起きるバグを発見したためそちらも未実装。


"""""以下制作メモ"""""

ジャンル:育成シミュレーション+リアルタイムバトルゲーム

パワプロのゲームモード"栄冠ナイン"を元にした育成ゲームをファンタジーな世界観で作る

本来野球の試合だった遊びはロックマンエグゼのバトルを元にしたシステムを組み込む。

//仕様の大雑把なメモ
手札使用で手札に書かれている日数分マスが進むすごろく
ゲーム内でキャラクターが育成学校に入学し、それぞれ能力値を伸ばしていく
上げたい能力値を一人ひとり設定し、日数が進むとそれに応じた経験値が入る
経験値が閾値に到達すると能力値が一つ上がる

日にちが進むと止まったマスのイベントが発生する
青ならいいイベント,赤なら悪いイベント,白はランダムなイベント

イベントは出来ればexcelで管理したい

一ヶ月を30日で固定,一年を12ヶ月とした暦で、3年間育成できる

一年に一回武闘大会を開催、ここで勝ち上がることがゲーム内の目標の一つ

3年立つと卒業し、冒険者ギルドに入るほか進路が決まる
卒業後のキャラクターたちはそれぞれギルド画面からある程度操作ができ、
指定した行動を自動的に行う(結果のみ出力する)

武器種別
剣
槍
杖
弓
拳

