# CPP Module 02

## keywords
- 'Ad-hoc polymorphism'
- 'operator overloading'
- 'Orthodox canonical form'

## ex00

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

