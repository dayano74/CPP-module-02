# CPP Module 02

## 目次
- [keywords](#keywords)
- [ex00](#ex00)
- [ex01](#ex01)
- [ex02](#ex02)

## keywords
- 'Ad-hoc polymorphism'
- 'operator overloading'
- 'Orthodox canonical form'

## ex00

- 目的: 固定小数点数を表す Fixed クラスを Orthodox Canonical Form で実装する。
- メンバ:
  - private: int _raw; static const int _fractionalBits = 8;（小数部は常に8ビット）
- パブリックAPI:
  - Fixed();            // _raw を 0 に初期化、"Default constructor called"
  - Fixed(const Fixed&);// "Copy constructor called"（必要なら *this = other で再利用）
  - Fixed& operator=(const Fixed& rhs); // 自己代入チェック、_rawコピー、"Copy assignment operator called"、return *this
  - ~Fixed();           // "Destructor called"
  - int getRawBits() const;      // ログして _raw を返す
  - void setRawBits(int raw);    // ログして _raw を設定
- 実行例の要旨:
  - main: Fixed a; Fixed b(a); Fixed c; c = b; getRawBits() を3回表示 → すべて 0。
  - 生成・コピー・代入・破棄・アクセサで所定のログが出る。
- メモ:
  - 初期化子リスト : _raw(0) は「生成時初期化」。
  - rhs = right-hand side（右辺）、*this は「自分自身（左辺）」。

- [整数と浮動小数点について](articles.md)

- Orthodox Canonical Form とは、
  - デフォルトコンストラクタ
  - コピーコンストラクタ
  - コピー代入演算子
  - デストラクタ
  の4つのメンバ関数を備えたクラスのこと。
  - これらを備えることで、オブジェクトの生成、コピー、代入、破棄が正しく行われることを保証する。
  - これにより、リソース管理やメモリ管理が適切に行われ、予期しない動作やメモリリークを防ぐことができる。
  - 例えば、動的にメモリを確保するクラスでは、コピーコンストラクタとコピー代入演算子を適切に実装しないと、複数のオブジェクトが同じメモリ領域を指すことになり、破棄時に二重解放が発生する可能性がある。
  - 逆に、これらのメンバ関数を適切に実装することで、オブジェクトのライフサイクルを正しく管理し、リソースの安全な使用が可能になる。

## ex01

### 目的
ex00 の Fixed クラスを「実用的」に拡張し、0.0 以外の値（整数・浮動小数点）を表現できるようにする。

### 追加/変更点
- 新コンストラクタ:
  - Fixed(const int value);    // int → 固定小数点
  - Fixed(const float value);  // float → 固定小数点
- 変換メンバ:
  - float toFloat() const;     // 内部表現 → float
  - int   toInt() const;       // 内部表現 → int（小数切り捨て）
- 出力演算子:
  - std::ostream& operator<<(std::ostream&, const Fixed&);
    - toFloat() を使い人間可読な値を出力。

### 固定小数点の基本
- 小数部ビット数 (_fractionalBits) = 8 → スケール係数 S = 2^8 = 256。
- 内部整数 _raw が表す実数値: real = _raw / 256.0f
- 実数 x を保存: _raw = roundf(x * 256)
- int n を保存: _raw = n << 8  (n * 256 と同等)
- int へ戻す: n = _raw >> 8
- float へ戻す: x = _raw / 256.0f

### 量子化誤差
- 刻み幅: 1/256 ≒ 0.00390625
- 最大誤差: 約 ±(1/512) ≒ 0.00195 （四捨五入使用時）
- 例: 0.1 → 0.1 * 256 = 25.6 → roundf = 26 → 表示 26/256 = 0.1015625

### roundf を使う理由
- (int)(x * 256) は 0 方向へ切り捨て → 系統的に小さめに偏る
- roundf(x * 256) は最も近い整数に丸め → 平均的にニュートラル
- 負数の扱いも一貫（-2.5 → -3 など「0 から遠ざかる方向」）

### なぜ float を << でシフトしないか
- ビットシフト演算子 << は整数型に対して定義。float を直接シフト不可。
- (int)value << 8 にすると小数部が最初に切り捨てられ精度喪失。
- 正しい手順: (value * 256) を丸めて整数化。

### f サフィックスの意味
- 42.42f / 1234.4321f の末尾 f は「これは float リテラル」
- f を付けないと double 型 → float へ縮小変換が発生
- オーバーロード解決で意図した Fixed(const float) を確実に選択させる目的にも有効

### static_cast<int>(...) を使う理由
- C 風キャスト(int) より意図が明確（通常の数値変換だけを要求）
- const 除去やビット再解釈など危険な変換を暗黙に混在させない
- レビューや検索性向上

### 「通常の数値変換だけ」とは
- 数値型 / 列挙型間など標準的で安全なコンパイル時に判定可能な変換のみ
- 再解釈 (reinterpret_cast) や const 除去 (const_cast) は行わない
- C 風キャストは状況によりこれらを複合的に試すため曖昧

### 実装ログメッセージ例
- "Default constructor called"
- "Int constructor called"
- "float constructor called" (大小統一は好みで調整可: "Float constructor called")
- "Copy constructor called"
- "Copy assignment operator called"
- "Destructor called"
- アクセサ: "getRawBits member function called" / "setRawBits member function called"

### 代表例での計算
- Fixed const c(42.42f): 42.42 * 256 ≒ 10859.52 → roundf=10860 → 表示 10860/256 ≒ 42.421875
- a = Fixed(1234.4321f): 1234.4321 * 256 ≒ 316,???.(計算詳細) → 丸め → toFloat() で近似表示
- Fixed const b(10): 10 << 8 = 2560 → toFloat()=10.0

### 詰まった箇所と解決メモ
1. 固定小数点の概念が曖昧
   - 対応: "内部整数 = 実数 × 2^8" と "表示時に逆変換" のワンフレーズで把握。
2. float でシフトできるか疑問
   - 対応: シフトは整数専用。float は乗算でスケール。
3. roundf の役割が不明
   - 対応: 量子化ステップへ最も近い整数へ丸め → 平均的誤差をゼロに。
4. (int) と static_cast<int> の違い
   - 対応: static_cast は安全・意図明確。C 風は複合的に試すので避ける。
5. static_cast の説明中 "通常の数値変換だけ" の意味
   - 対応: 危険キャスト (reinterpret/const/dynamic) を含まないこと。
6. リテラル末尾 f の意味
   - 対応: double ではなく最初から float 型。意図明示 & 余計な縮小変換回避。
7. 量子化誤差の大きさが不安
   - 対応: 刻み 1/256, 最大誤差 ≒ 0.00195 と数値化して把握。

### チェックリスト
- int 変換: raw == value << 8 ?
- float 変換: raw ≒ roundf(f * 256) ?
- toInt(): raw >> 8 で期待通りか?
- toFloat(): raw / 256.0f で ±0.002 以内の誤差か?
- operator<< は toFloat() を利用しているか?
- ログ文言は課題仕様と整合?

### 追加アイデア（任意）
- ヘルパー: static inline int scale() { return 1 << _fractionalBits; }
- デバッグ用関数: printRawHex() など
- 今後の演算子オーバーロード拡張への足場

## ex02
