#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }


    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};

void RleCodec::encode()
{
    std::stringstream os;
    int length=0;
    int count1=0;
    int index = 0, index_d = 0;
    char cur;
    cur = code_str[0];

    for (auto c : code_str) {
        length++;
    }

    char d=code_str[index_d];
    while (length>=0) {
        if(cur==d) {
            length--;
            count1++;
            //cur = *(code_str+1);
        } else if(cur!=d) {
            index += count1;
            //cur = code_str[index];
            length--;
            os << 'Q';

            while (count1>0) {
                if (count1>26) {
                    os << 'Z' << cur << 'Q';
                    count1 -= 26;
                } else {
                    char ans;
                    ans = (char)count1 + 'A' - 1;
                    os << ans << cur;
                    count1 = 0;
                }
            }

            cur = code_str[index];
            count1 = 1;
        }
        index_d++;
        d=code_str[index_d];
    }

    code_str = os.str();
	encoded = true;

}

void RleCodec::decode()
{
	std::stringstream os;
	//std::string int_str;
	char q = 'A';
	char number = ' ';
	int cnt = 0;
	for (auto c : code_str) {
        if (q=='A') {
            q = c;
		}else if(number == ' '){
            number = c;
		}
        else {
            //int_str.push_back(c);
			int cnt = 0;
            cnt = number - 'A' +1;
            for (int i=0; i<cnt; ++i)
					os << c;
			//int_str.clear();
			number = ' ';
			q = 'A';
		}
	}

	code_str = os.str();
	encoded = false;
}


std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}


int main()
{
    std::string input_string;
    std::cin >> input_string;

    DummyCodec dummy{input_string};
    encode_decode(dummy);
    std::cout << "Dummy encoding: ";
    std::cout << dummy << std::endl;
    encode_decode(dummy);
    std::cout << "Dummy decoding: ";
    std::cout << dummy << std::endl;

    RleCodec rle{input_string};
    encode_decode(rle);
    std::cout << "RLE encoding: ";
    std::cout << rle << std::endl;
    encode_decode(rle);
    std::cout << "RLE decoding: ";
    std::cout << rle << std::endl;
}
