#include <stdio.h>
#include <string.h>

#define MAX_VE 100

// Định nghĩa cấu trúc VeMayBay theo đề bài
struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    double cuocHanhLy;
};

int main() {
    int n;
    struct VeMayBay danhSachVe[MAX_VE];

    // 1. Nhập số lượng vé với điều kiện kiểm chuẩn 1 <= N <= 100
    printf("Nhập số lượng vé máy bay: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_VE) {
        printf("Lỗi: Số lượng vé phải nằm trong khoảng từ 1 đến 100!\n");
        return 0;
    }
    while (getchar() != '\n'); // Làm sạch bộ đệm sau khi nhập số

    // 2. Nhập danh sách vé máy bay
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhập thông tin vé thứ %d ---\n", i + 1);

        printf("Mã vé PNR: ");
        scanf("%s", danhSachVe[i].maVe);
        while (getchar() != '\n');

        printf("Họ tên hành khách: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = '\0';

        printf("Hạng vé (Business/Deluxe/Eco): ");
        scanf("%s", danhSachVe[i].hangVe);
        while (getchar() != '\n');

        // Kiểm chuẩn cân nặng hành lý không âm
        do {
            printf("Khối lượng hành lý ký gửi (kg): ");
            if (scanf("%f", &danhSachVe[i].canNangHanhLy) != 1 || danhSachVe[i].canNangHanhLy < 0) {
                printf("Lỗi: Khối lượng hành lý phải là số không âm! Vui lòng nhập lại.\n");
                while (getchar() != '\n');
                danhSachVe[i].canNangHanhLy = -1;
            } else {
                while (getchar() != '\n');
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        // 3. Tự động tính cước hành lý theo quy tắc nghiệp vụ
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20.0f) {
                danhSachVe[i].cuocHanhLy = 0.0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20.0f) * 50000.0;
            }
        } else { // Eco hoặc Deluxe
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000.0;
        }
    }

    // 4. Hiển thị danh sách dạng bảng căn chỉnh cột & Thống kê tổng tiền, hành lý nặng nhất
    double tongTienCuoc = 0;
    int maxIndex = 0;

    printf("\n================================== DANH SÁCH VÉ MÁY BAY CHUYẾN BAY ==================================\n");
    printf("%-5s | %-12s | %-25s | %-12s | %12s | %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
    printf("----------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-5d | %-12s | %-25s | %-12s | %12.1f | %15.0f\n", 
            i + 1, 
            danhSachVe[i].maVe, 
            danhSachVe[i].tenHanhKhach, 
            danhSachVe[i].hangVe, 
            danhSachVe[i].canNangHanhLy, 
            danhSachVe[i].cuocHanhLy);

        tongTienCuoc += danhSachVe[i].cuocHanhLy;

        if (danhSachVe[i].canNangHanhLy > danhSachVe[maxIndex].canNangHanhLy) {
            maxIndex = i;
        }
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tổng tiền cước hành lý toàn chuyến: %.0f VNĐ\n", tongTienCuoc);
    printf("Vé có hành lý ký gửi nặng nhất: %s - %s (%.1f kg)\n", 
        danhSachVe[maxIndex].maVe, 
        danhSachVe[maxIndex].tenHanhKhach, 
        danhSachVe[maxIndex].canNangHanhLy);

    // 5. Cập nhật thông tin hành lý theo mã PNR tìm kiếm
    char searchPNR[15];
    printf("\n--- CẬP NHẬT THÔNG TIN HÀNH LÝ ---\n");
    printf("Nhập mã vé PNR cần cập nhật hành lý: ");
    scanf("%s", searchPNR);
    while (getchar() != '\n');

    int foundIndex = -1;
    for (int i = 0; i < n; i++) {