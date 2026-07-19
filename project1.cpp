#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;
const int MAX = 100;
// Định nghĩa cấu trúc date để sử dụng cho ngaySinh
struct date {
    int ngay;
    int thang;
    int nam;
};

// Định nghĩa cấu trúc SinhVien
struct SinhVien {
    int id;
    char ten[50];
    char gioiTinh[5];
    date ngaySinh;
    int tuoi;
    float diemMon1;
    float diemMon2;
    float diemMon3;
    float diemTrungBinh;
    char hocLuc[10];
    char maLop[30];
};

// Khai báo alias SV đại diện cho struct SinhVien
typedef struct SinhVien SV;

// ==========================================
// CÁC HÀM HỖ TRỢ TRÁNH TRÔI LỆNH & XỬ LÝ CHUỖI
// ==========================================

// Hàm xóa ký tự xuống dòng ở cuối chuỗi do fgets để lại
void xoaXuongDong(char x[]) {
    size_t len = strlen(x);
    if (len > 0 && x[len - 1] == '\n') {
        x[len - 1] = '\0';
    }
}

// Hàm dọn dẹp bộ nhớ đệm bàn phím, tránh bị trôi lệnh fgets sau khi dùng scanf
void xoaBoNhoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==========================================
// ĐỊNH NGHĨA CÁC HÀM NHẬP / XUẤT
// ==========================================
void inSinhVien(SV sv) {
    // Đã sửa lỗi viết hoa/thường các thuộc tính và thêm tham số sv.hocLuc vào printf
    printf("\n%d \t %s \t %s \t %02d/%02d/%d \t %d \t %.2f \t %.2f \t %.2f \t %.2f \t %s \t %s\n",
        sv.id,
        sv.ten,
        sv.gioiTinh,
        sv.ngaySinh.ngay,
        sv.ngaySinh.thang,
        sv.ngaySinh.nam,
        sv.tuoi,
        sv.diemMon1,
        sv.diemMon2,
        sv.diemMon3,
        sv.diemTrungBinh,
        sv.hocLuc,
        sv.maLop);
}
void tinhDiemTrungBinh(SV sv[], int n) {
    for (int i = 0;i < n;i++) {
        sv[i].diemTrungBinh = (sv[i].diemMon1 + sv[i].diemMon2 + sv[i].diemMon3) / 3;
    }
}

void tinhTuoi(SV sv[], int n) {

    time_t TIME = time(0);
    tm* NOW = localtime(&TIME); // Đã thêm dấu & để sửa lỗi cú pháp chuẩn C++
    int namHienTai = NOW->tm_year + 1900;
    for (int i = 0;i < n;i++) {
        sv[i].tuoi = namHienTai - sv[i].ngaySinh.nam;
    }
}
void nhapSinhVien(SV& sv) {
    printf("\n--- NHAP THONG TIN SINH VIEN ---\n");

    printf("Nhap ID: ");
    scanf("%d", &sv.id); // Đã sửa '%d' thành "%d"
    xoaBoNhoDem(); // Xóa bộ đệm sau khi nhập số

    printf("Nhap Ten: ");
    fgets(sv.ten, sizeof(sv.ten), stdin);
    xoaXuongDong(sv.ten);

    printf("Nhap Gioi tinh: ");
    fgets(sv.gioiTinh, sizeof(sv.gioiTinh), stdin);
    xoaXuongDong(sv.gioiTinh);

    // Đã sửa thứ tự nhập tự nhiên: Ngày -> Tháng -> Năm và sửa lỗi viết hoa/thường ngaySinh
    printf("Nhap Ngay sinh (ngay thang nam cách nhau bởi khoảng trắng): ");
    scanf("%d%d%d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);

    printf("Nhap Diem mon 1: ");
    scanf("%f", &sv.diemMon1);

    printf("Nhap Diem mon 2: ");
    scanf("%f", &sv.diemMon2);

    printf("Nhap Diem mon 3: ");
    scanf("%f", &sv.diemMon3);
    xoaBoNhoDem(); // Xóa bộ đệm sau khi nhập số để chuẩn bị fgets tiếp theo

    printf("Nhap Ma lop: ");
    fgets(sv.maLop, sizeof(sv.maLop), stdin); // Đã sửa malop thành maLop
    xoaXuongDong(sv.maLop);

    // Tạm thời gán mặc định các giá trị chưa tính toán để tránh in ra giá trị rác
    sv.tuoi = 0;

    strcpy(sv.hocLuc, "Chua_xet");
}


// Khai báo prototype các hàm còn lại (bạn sẽ tự code tiếp bên dưới)
/*

void xepLoai(SV& sv);
void capNhatSinhVien(SV& sv);

void nhapDanhSachSinhVien(SV ds[], int& n);
void xuatDanhSachSinhVien(SV ds[], int n);

float timMax_DiemTrungBinh(SV ds[], int n);
int timMin_Tuoi(SV ds[], int n);

void xuatDanhSachSinhVienXepLoaiGioi(SV ds[], int n);
void xuatDanhSachSinhVienTheoLop(SV ds[], int n, char{
int timSinhVienTheoTen(SV ds[], int n, char ten[]);
void xoaSinhVienTheoId(SV ds[], int& n, char ten[]);

void sapXepDanhSachSinhVienTheoDTB(SV ds[], int n);
void sapXepDanhSachSinhVienTheoTen(SV ds[], int n); */

// ==========================================
// HÀM MAIN ĐỂ CHẠY THỬ
// ==========================================

int main() {
    SV sv1[MAX];
    int n;
    do {
        printf("Nhap so luong sinh vien (1-%d): ", MAX);
        scanf("%d", &n);
        if (n <= 0 || n > MAX) {
            printf("So luong sinh vien khong hop le. Vui long nhap lai.\n");
        }
    } while (n <= 0 || n > MAX);
    int i = 0;
    for (int i = 0;i < n;i++) {
        nhapSinhVien(sv1[i]);
    }
    tinhTuoi(sv1, n);           // Truyền tham chiếu thông thường
    tinhDiemTrungBinh(sv1, n); // Truyền địa chỉ (dấu &) vì hàm yêu cầu con trỏ

    printf("\nID \t Ten \t\t GT \t Ngay sinh \t Tuoi \t Mon 1 \t Mon 2 \t Mon 3 \t ĐTB \t Xep loai \t Ma lop");
    printf("\n------------------------------------------------------------------------------------------------------");







    for (int i = 0;i < n;i++) {
        inSinhVien(sv1[i]);
    }
    return 0;
}