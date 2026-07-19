#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include <stdio.h>
using namespace std;
const int MAX = 100;
void ham_viet_hoa_dung(char a[]) {
	int i = 0;
	while (a[i] != '\0') {
		if (a[i] >= 65 && a[i] <= 90) {
			a[i] += 32;
		}
		i++;
	}
	i = 0;
	if (a[0] >= 'a' && a[0] <= 'z') {
		a[0] = a[0] - 32;
	}
	while (a[i] != '\0') {
		if (a[i] == ' ' && a[i + 1] != '\0') {
			if (a[i + 1] >= 'a' && a[i + 1] <= 'z') {
				a[i + 1] = a[i + 1] - 32;
			}
		}
		i++;
	}
}
void ham_xoa_khoang_trang(char a[]) {
	int read = 0;
	int write = 0;
	while (a[read] == ' ') {
		read++;
	}
	bool flag = false;
	while (a[read] != '\0') {

		if (a[read] != ' ') {
			a[write] = a[read];
			write++;
			flag = false;
		}
		else if (!flag) {
			a[write] = a[read];
			write++;
			flag = true;
		}
		read++;
	}
	if (write > 0 && a[write - 1] == ' ') {
		write--;
	}
	a[write] = '\0';
}
struct date {
	int ngay;
	int thang;
	int nam;
};

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
	char hocLuc[20];
	char maLop[30];
};
typedef struct SinhVien SV;

void xoaXuongDong(char x[]) {
	size_t len = strlen(x);
	if (len > 0 && x[len - 1] == '\n') {
		x[len - 1] = '\0';
	}
}

void xoaBoNhoDem() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void inSinhVien(SV sv) {
	printf("%d \t %s \t %s \t %02d/%02d/%d \t %d \t %.2f \t %.2f \t %.2f \t %.2f \t %s \t %s\n",
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
	for (int i = 0; i < n; i++) {
		sv[i].diemTrungBinh = (sv[i].diemMon1 + sv[i].diemMon2 + sv[i].diemMon3) / 3;
	}
}

void tinhTuoi(SV sv[], int n) {
	time_t TIME = time(0);
	tm* NOW = localtime(&TIME);
	int namHienTai = NOW->tm_year + 1900;
	for (int i = 0; i < n; i++) {
		sv[i].tuoi = namHienTai - sv[i].ngaySinh.nam;
	}
}

void my_strcpy(char a[], char b[]) {
	int i = 0;
	while (b[i] != '\0') {
		a[i] = b[i];
		i++;
	}
	a[i] = '\0';
}

void xephocluc(SV sv1[], int n) {
	for (int i = 0; i < n; i++) {
		float dtb = sv1[i].diemTrungBinh;
		if (dtb >= 9) {
			char b[] = "Xuat Sac";
			my_strcpy(sv1[i].hocLuc, b);
		}
		else if (dtb >= 8) {
			char b[] = "Gioi";
			my_strcpy(sv1[i].hocLuc, b);
		}
		else if (dtb >= 6.5) {
			char b[] = "Kha";
			my_strcpy(sv1[i].hocLuc, b);
		}
		else if (dtb >= 5) {
			char b[] = "Trung Binh";
			my_strcpy(sv1[i].hocLuc, b);
		}
		else {
			char b[] = "Yeu";
			my_strcpy(sv1[i].hocLuc, b);
		}
	}
}

float timMax_DiemTrungBinh(SV ds[], int n) {
	float max = ds[0].diemTrungBinh;
	for (int i = 1; i < n; i++) {
		if (max < ds[i].diemTrungBinh) {
			max = ds[i].diemTrungBinh;
		}
	}
	return max;
}

int timMin_Tuoi(SV ds[], int n) {
	int min = ds[0].tuoi;
	for (int i = 1; i < n; i++) {
		if (min > ds[i].tuoi) {
			min = ds[i].tuoi;
		}
	}
	return min;
}

void nhapSinhVien(SV& sv) {
	printf("\n--- NHAP THONG TIN SINH VIEN ---\n");

	printf("Nhap ID: ");
	scanf("%d", &sv.id);
	xoaBoNhoDem();

	printf("Nhap Ten: ");
	fgets(sv.ten, sizeof(sv.ten), stdin);
	xoaXuongDong(sv.ten);

	printf("Nhap Gioi tinh: ");
	fgets(sv.gioiTinh, sizeof(sv.gioiTinh), stdin);
	xoaXuongDong(sv.gioiTinh);

	printf("Nhap Ngay sinh (ngay thang nam cach nhau boi khoang trang): ");
	scanf("%d%d%d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);

	printf("Nhap Diem mon 1: ");
	scanf("%f", &sv.diemMon1);

	printf("Nhap Diem mon 2: ");
	scanf("%f", &sv.diemMon2);

	printf("Nhap Diem mon 3: ");
	scanf("%f", &sv.diemMon3);
	xoaBoNhoDem();

	printf("Nhap Ma lop: ");
	fgets(sv.maLop, sizeof(sv.maLop), stdin);
	xoaXuongDong(sv.maLop);
}

int dem_so_luong_ky_tu(char a[]) {
	int i = 0;
	int count = 0;
	while (a[i] != '\0') {
		count++;
		i++;
	}
	return count;
}

int my_strcmp(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0' || b[i] != '\0') {
		if (a[i] != b[i]) {
			return 1;
		}
		i++;
	}
	return 0;
}

void xuatDanhSachSinhVienXepLoaiXuatSac(SV ds[], int n) {
	printf("\n danh sach sv loai xuat sac ");
	int q = 0;
	for (int i = 0; i < n; i++) {
		char mau[] = "Xuat Sac";
		if (my_strcmp(ds[i].hocLuc, mau) == 0) {
			inSinhVien(ds[i]);
			printf("\n");
			q++;
		}
	}
	if (q == 0) {
		printf("\n lop khong co sinh vien xuat sac");
	}
}

void xuatDanhSachSinhVienTheoLop(SV sv1[], int n, char a[]) {
	printf("\n danh sach sv thuoc lop %s ", a);
	int q = 0;
	for (int i = 0; i < n; i++) {
		if (my_strcmp(sv1[i].maLop, a) == 0) {
			inSinhVien(sv1[i]);
			printf("\n");
			q++;
		}
	}
	if (q == 0) {
		printf("\n lop %s khong co sinh vien nao!", a);
	}
}

void tra_ten_cuar_sv(char a[], char w[]) {
	int count = dem_so_luong_ky_tu(a) - 1;
	// SỬA LỖI: Thêm điều kiện count >= 0 để tránh crash nếu chuỗi rỗng
	while (count >= 0 && (a[count] == ' ' || a[count] == '\n' || a[count] == ',' || a[count] == '.')) {
		count--;
	}
	int i = 0;
	// SỬA LỖI: Đảo count >= 0 lên trước để tránh lỗi đọc bộ nhớ âm a[-1]
	while (count >= 0 && a[count] != ' ') {
		w[i++] = a[count];
		count--;
	}
	w[i] = '\0';

	// Lat nguoc ten lai
	int left = 0;
	int right = i - 1;
	while (left < right) {
		char temp = w[left];
		w[left] = w[right];
		w[right] = temp;
		left++;
		right--;
	}
}

void timSinhVienTheoTen(SV ds[], int n, char r[]) {
	printf("\n danh sach sv co ten %s ", r);
	char w[50];
	int q = 0;
	for (int i = 0; i < n; i++) {
		tra_ten_cuar_sv(ds[i].ten, w);
		if (my_strcmp(w, r) == 0) {
			inSinhVien(ds[i]);
			printf("\n");
			q++;
		}
	}
	if (q == 0) {
		printf("\n %s ko co sinh vien nay trong danh sach", r);
	}
}

void xoaSinhVienTheoId(SV ds[], int& n, int id) {
	printf("\n danh sach sv co id %d ", id);
	int q = 0;
	for (int i = 0; i < n; i++) {
		if (ds[i].id == id) {
			int j = i;
			while (j < n - 1) {
				ds[j] = ds[j + 1];
				j++;
			}
			i--;
			n--;
			q++;
		}
	}
	if (q == 0) {
		printf("\n %d ko co id sinh vien nay trong danh sach", id);
	}
	else {
		printf("\nDa xoa thanh cong %d sinh vien co ID %d khoi danh sach.", q, id);
	}
}

void sapXepDanhSachSinhVienTheoDTB(SV ds[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (ds[i].diemTrungBinh > ds[j].diemTrungBinh) {
				SV temp = ds[i];
				ds[i] = ds[j];
				ds[j] = temp;
			}
		}
	}
}

int dem_chu(char a[]) {
	int sum = 0;
	for (int i = 0; a[i] != '\0'; i++) {
		if (a[i] == ' ') {
			sum++;
		}
	}
	sum++;
	return sum;
}

int ham_so_sanh_ten(char a[], char b[]) {
	int left = dem_so_luong_ky_tu(a);
	int right = dem_so_luong_ky_tu(b);
	int j = (left < right) ? left : right;
	int i = 0;

	while (i < j) {
		char ky_tu1 = (a[i] >= 65 && a[i] <= 90) ? a[i] + 32 : a[i];
		char ky_tu2 = (b[i] >= 65 && b[i] <= 90) ? b[i] + 32 : b[i];
		if (ky_tu1 < ky_tu2) {
			return -1;
		}
		else if (ky_tu1 > ky_tu2) {
			return 1;
		}
		i++;
	}
	if (left < right) {
		return -1;
	}
	else if (left > right) {
		return 1;
	}
	return 0;
}

int ham_so_sanh_chuoi(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0' || b[i] != '\0') {
		char ky_tu1 = (a[i] >= 65 && a[i] <= 90) ? a[i] + 32 : a[i];
		char ky_tu2 = (b[i] >= 65 && b[i] <= 90) ? b[i] + 32 : b[i];
		if (ky_tu1 < ky_tu2) {
			return -1;
		}
		else if (ky_tu1 > ky_tu2) {
			return 1;
		}
		i++;
	}
	return 0;
}

void sapXepDanhSachSinhVienTheoTen(SV ds[], int n) {
	for (int i = 0; i < n - 1; i++) {
		char w[50];
		char z[50];

		for (int j = i + 1; j < n; j++) {
			tra_ten_cuar_sv(ds[i].ten, w);
			tra_ten_cuar_sv(ds[j].ten, z);

			int ket_qua = ham_so_sanh_ten(w, z);

			if (ket_qua > 0) {
				SV temp = ds[i];
				ds[i] = ds[j];
				ds[j] = temp;
			}
			else if (ket_qua == 0) {
				int ket_qua_ho_ten = ham_so_sanh_chuoi(ds[i].ten, ds[j].ten);

				if (ket_qua_ho_ten > 0) {
					SV temp = ds[i];
					ds[i] = ds[j];
					ds[j] = temp;
				}
				else if (ket_qua_ho_ten == 0) {
					if (ds[i].id > ds[j].id) {
						SV temp = ds[i];
						ds[i] = ds[j];
						ds[j] = temp;
					}
				}
			}
		}
	}
}

void capNhatSinhVien(SV sv1[], int& n) {
	for (int i = 0; i < n; i++) {
		// Chuẩn hóa Tên
		ham_viet_hoa_dung(sv1[i].ten);
		ham_xoa_khoang_trang(sv1[i].ten);
		// BỔ SUNG: Chuẩn hóa cả Mã Lớp cho đồng bộ
		ham_viet_hoa_dung(sv1[i].maLop);
		ham_xoa_khoang_trang(sv1[i].maLop);
	}

	tinhTuoi(sv1, n);
	tinhDiemTrungBinh(sv1, n);
	xephocluc(sv1, n);

	printf("\nID \t Ten \t\t GT \t Ngay sinh \t Tuoi \t Mon 1 \t Mon 2 \t Mon 3 \t DTB \t Xep loai \t Ma lop\n");
	printf("------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		inSinhVien(sv1[i]);
	}
	printf("\n max dtb= %.2f", timMax_DiemTrungBinh(sv1, n));
	printf("\n min tuoi= %d\n", timMin_Tuoi(sv1, n));

	xuatDanhSachSinhVienXepLoaiXuatSac(sv1, n);

	char lopCanTim[30];
	printf("\nNhap ma lop ban muon tim kiem: ");
	fgets(lopCanTim, sizeof(lopCanTim), stdin);
	xoaXuongDong(lopCanTim);
	// BỔ SUNG: Chuẩn hóa từ khóa lớp trước khi tìm
	ham_viet_hoa_dung(lopCanTim);
	ham_xoa_khoang_trang(lopCanTim);
	xuatDanhSachSinhVienTheoLop(sv1, n, lopCanTim);

	char tenCanTim[30];
	printf("\nNhap ten sinh vien muon tim kiem (chi nhap ten, vi du: An): ");
	fgets(tenCanTim, sizeof(tenCanTim), stdin);
	xoaXuongDong(tenCanTim);
	// BỔ SUNG: Chuẩn hóa từ khóa tên trước khi tìm
	ham_viet_hoa_dung(tenCanTim);
	ham_xoa_khoang_trang(tenCanTim);
	timSinhVienTheoTen(sv1, n, tenCanTim);

	int idXoa;
	printf("\nNhap ID sinh vien muon xoa: ");
	scanf("%d", &idXoa);
	xoaBoNhoDem();

	xoaSinhVienTheoId(sv1, n, idXoa);

	printf("\n--- DANH SACH SAU KHI XOA ---\n");
	for (int i = 0; i < n; i++) {
		inSinhVien(sv1[i]);
	}

	sapXepDanhSachSinhVienTheoTen(sv1, n);
	printf("\n\n--- DANH SACH SAU KHI SAP XEP THEO TEN (A-Z) ---\n");
	printf("ID \t Ten \t\t GT \t Ngay sinh \t Tuoi \t Mon 1 \t Mon 2 \t Mon 3 \t DTB \t Xep loai \t Ma lop\n");
	printf("------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		inSinhVien(sv1[i]);
	}

	sapXepDanhSachSinhVienTheoDTB(sv1, n);
	printf("\n\n--- DANH SACH SAU KHI SAP XEP THEO DIEM TRUNG BINH TANG DAN ---\n");
	printf("ID \t Ten \t\t GT \t Ngay sinh \t Tuoi \t Mon 1 \t Mon 2 \t Mon 3 \t DTB \t Xep loai \t Ma lop\n");
	printf("------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		inSinhVien(sv1[i]);
	}
}

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
	for (int i = 0; i < n; i++) {
		nhapSinhVien(sv1[i]);
	}
	capNhatSinhVien(sv1, n);

	return 0;
}