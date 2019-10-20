# Program Presensi untuk Dosen
Sistem absen manual(dipanggil satu per-satu) memang membantu mencegah  mahasiswa yang selalu titip absen(tipsen). Namun, cara tersebut kurang efektif karna terkadang terjadi kesalahan ketika melihat nama mahasiswa terutama untuk beberapa dosen yang sudah berumur, lalu akan sangat sulit menentukan mana mahasiswa yang bisa mengikuti/tidak mengikuti UTS maupun UAS. Oleh karena itu, kami mencoba untuk membuat sebuah program yang membantu masalah tersebut dimana program ini akan memunculkan nama mahasiswa dan dosen hanya perlu memanggil nama yang dimunculkan program,lalu dosen akan mengetahui mahasiswa yang bersangkutan hadir atau tidaknya dengan memilih menu yes ataupun no. Selanjutnya,pada saat UTS/UAS dosen dapat mengetahui apakah mahasiswa tersebut bisa mengikuti ujian atau tidak.
## Detail kelompok
No Kelompok: 01

Alvin Audinata (1806200204)

Gilbert Parluhutan Siagian (1806148681)

## Tahap persiapan

Untuk menjalankan program ini di komputer Anda, Anda perlu memiliki Bloodshed Dev C++ terpasang di komputer Anda. Bloodshed Dev C++ tersedia dalam berbagai versi, tetapi sangat direkomendasikan untuk memakai Dev C++ versi terbaru (5.11). Berikut ini langkah-langkah pemasangannya:

1. Unduh Dev C++ 5.11 melalui link [ini](https://sourceforge.net/settings/mirror_choices?projectname=dev-cpp&filename=Binaries/Dev-C%2B%2B%204.9.9.2/devcpp-4.9.9.2_setup.exe&selected=nchc).
2. Ikuti prosedur standar pemasangan yang tersedia (tidak perlu mengubah pengaturan)

Setelah terpasang, buka, dan ikuti langkah-langkah berikut:
1. Untuk sementara, abaikan dahulu kotak dialog yang muncul terkait penyesuaian tampilan dst.
2. Buka menu Tools -> Compiler Options
3. Pada tab General, centang "Add the following commands when calling the compiler:", kemudian masukkan `-std=c11` pada text box di bawahnya.

Setelah itu, unduh salinan dari program ini, kemudian buka dengan Dev C++. Setelah terbuka, jalankan dengan menggunakan F11.

## Fitur utama
### Memungkinkan dosen untuk input matkul secara mandiri
Fleksibel, mata kuliah ("matkul") yang dimasukkan dapat disesuaikan dengan kebutuhan dosen. Jika ada yang sudah tidak dibutuhkan, matkul tersebut dapat dihapus untuk mempermudah pengelolaan.
### Proteksi presensi lapis ganda
Fitur ini mencegah dosen melakukan presensi di luar jam kuliah atau di luar periode kuliah, sehingga kesalahan akibat ketidaksengajaan atau tangan orang lain dapat diminimalisasi.
### Rekapitulasi data
Setelah minimal melakukan satu kali presensi di sebuah mata kuliah, dosen dapat melihat rekap presensi kelas tersebut per mahasiswa, bahkan menentukan dapat/tidaknya mahasiswa tersebut mengikuti ujian (Baik UTS maupun UAS).

## Info lanjut
Jika ingin mengetahui lebih detail mengenai mekanisme program, silahkan rujuk ke [sini](https://drive.google.com/file/d/1NCET2fGuIe4cesh_OTSzWloBByqTZVE5/view?usp=drivesdk).
