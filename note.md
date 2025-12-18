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

### 目的
Fixed クラスを「本当の数値型」のように使えるようにする。
比較・四則演算・インクリメント/デクリメント・min/max を追加し、演算子オーバーロードを完成させる。

### 追加する演算子・関数

| 種類 | 演算子/関数 | 備考 |
|------|------------|------|
| 比較演算子（6種） | `> < >= <= == !=` | raw 同士の比較で実装 |
| 算術演算子（4種） | `+ - * /` | `*` `/` はスケール調整が必要 |
| インクリメント/デクリメント（4種） | `++a` `a++` `--a` `a--` | raw を ±1 する（最小刻み ε） |
| 静的メンバ関数（4種） | `min` `max` 各2種（const版/非const版） | 参照を返す |

---

### 1. 最小の表現可能な ε（イプシロン）とは？

`_fractionalBits = 8` のとき、固定小数点の刻みは `1/256`。

- **ε = 1/256 = 0.00390625**

これが「raw を 1 だけ変化させたときの実値の変化量」。

#### なぜ `1 + ε > 1` という定義？
「1 より大きい最小の値を作れる幅」という意味。
- Fixed(1) の raw = 256
- Fixed(1 + ε) の raw = 257
- toFloat() = 257/256 = 1.00390625 > 1 ✓

つまり **raw を ±1 すること = ε だけ変化させること**。

---

### 2. 算術演算子の実装

#### `+` と `-`：raw 同士の加減算でOK
理由：
- A = ra / 256, B = rb / 256
- A + B = (ra + rb) / 256

なので `result.raw = ra + rb` で正しい。

```cpp
Fixed Fixed::operator+(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits(_raw + rhs._raw);
  return r;
}
```

#### `*`：スケール調整（`>> 8`）が必要な理由
乗算では分母が2回かかる：
- A × B = (ra/256) × (rb/256) = (ra × rb) / 256²

Fixed は「raw / 256」で表すので、256 を一回戻す必要がある：
- **result.raw = (ra × rb) / 256 = (ra × rb) >> 8**

```cpp
Fixed Fixed::operator*(const Fixed& rhs) const {
  Fixed r;
  long tmp = static_cast<long>(_raw) * static_cast<long>(rhs._raw);
  r.setRawBits(static_cast<int>(tmp >> _fractionalBits));
  return r;
}
```

#### `/`：スケール調整（`<< 8`）が必要な理由
除算では分母が消える：
- A / B = (ra/256) / (rb/256) = ra / rb

でも Fixed 形式は「raw / 256」なので、分子を 256 倍してから割る：
- **result.raw = (ra × 256) / rb = (ra << 8) / rb**

```cpp
Fixed Fixed::operator/(const Fixed& rhs) const {
  Fixed r;
  long numerator = (static_cast<long>(_raw) << _fractionalBits);
  r.setRawBits(static_cast<int>(numerator / rhs._raw));
  return r;
}
```

#### `long` を使う理由（オーバーフロー対策）
`ra * rb` は int 同士の掛け算だとオーバーフローしやすい。
例：ra = 25600, rb = 25600 → 655,360,000（まだ int に収まるが、もう少し大きいとダメ）
安全のため `long` または `long long` にキャストしてから計算する。

---

### 3. インクリメント/デクリメント

#### 前置 `++a` と後置 `a++` の違い

| 種類 | 戻り値 | 意味 |
|------|--------|------|
| 前置 `++a` | `Fixed&`（参照） | インクリメント**後**の値を返す |
| 後置 `a++` | `Fixed`（コピー） | インクリメント**前**の値を返す |

```cpp
// 前置: 変更後の自分自身への参照を返す
Fixed& Fixed::operator++() {
  ++_raw;
  return *this;
}

// 後置: 変更前のコピーを返す
Fixed Fixed::operator++(int) {
  Fixed before(*this);  // 変更前をコピー
  ++_raw;
  return before;
}
```

#### 引数 `int` の意味（ダミー引数）
C++ では前置と後置を区別するために、後置には `int` のダミー引数を付ける。
実際には使わない。コンパイラが `a++` を見ると `operator++(0)` を呼び出す。

---

### 4. min / max

#### なぜ const 版と非 const 版の両方が必要？
C++ では「const オブジェクトを非 const 参照で受け取れない」から。

```cpp
Fixed a(1);
Fixed const b(2);

Fixed::min(a, b);  // ← b が const なので、非 const 版は呼べない
```

const 版があれば、const オブジェクトも受け取れる。

#### 戻り値が「参照」である理由
- コピーを作らず効率的
- 「引数のどちらかそのもの」を返すので、参照が自然
- 呼び出し側が結果を変更したい場合に対応できる（非 const 版）

```cpp
Fixed& Fixed::min(Fixed& a, Fixed& b) {
  return (a._raw < b._raw) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
  return (a._raw < b._raw) ? a : b;
}
```

---

### 5. 出力の検証

#### `0.00390625` はなぜこの値？
`++a` は raw を 1 増やす。
- 初期：raw = 0 → toFloat() = 0/256 = 0
- `++a` 後：raw = 1 → toFloat() = 1/256 = **0.00390625**

#### `5.05f * 2` が `10.1016` になる計算過程

1. `Fixed(5.05f)`：
   - raw = roundf(5.05 × 256) = roundf(1292.8) = 1293

2. `Fixed(2)`：
   - raw = 2 << 8 = 512

3. 乗算 `1293 * 512`：
   - tmp = 1293 × 512 = 662016
   - result.raw = 662016 >> 8 = 2586

4. `toFloat()`：
   - 2586 / 256 = 10.1015625

5. `cout` の表示精度で **10.1016** と出る

---

### チェックリスト

- [ ] 比較演算子: `==` は `_raw == rhs._raw`、`!=` は `_raw != rhs._raw` になっているか？（`<=` の typo に注意）
- [ ] 乗算: `long` にキャストしてから掛け算 → `>> 8` しているか？
- [ ] 除算: 分子を `<< 8` してから割っているか？ゼロ除算の扱いは？
- [ ] 前置++: `Fixed&` を返しているか？
- [ ] 後置++: `Fixed`（コピー）を返しているか？ダミー引数 `int` があるか？
- [ ] min/max: const 版の比較が正しいか？（`<` と `>` を間違えていないか）

---

### 典型的なバグと対策

| バグ | 症状 | 対策 |
|------|------|------|
| `operator==` が `<=` になっている | 全ての比較で true/false がおかしくなる | コピペ時に確認 |
| `min` の const 版で `>` を使っている | min なのに max の挙動になる | ロジック確認 |
| 乗算で `long` を使わない | 大きな値でオーバーフロー | キャストを忘れない |
| 後置++で `Fixed&` を返す | コンパイルは通るが意味が間違う | 後置はコピーを返す |
