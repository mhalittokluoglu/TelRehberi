# TelRehberi
Telefon rehberi oluşturan program 

### Windows
- Windows klasörünün içindeki Rehber.csv'yi bir editör ile açınız. Editör NotePad olabilir.
- Boş bir Metin Belgesi oluşturun ve Rehber.csv formatında olduğu gibi isimleri kaydedin.
    - İsim,Numara
- Daha sonra bu oluşturduğunuz Metin Belgesinin uzantısını .csv olarak değiştirin.
    - Örnek: Diyelim ki Metin Belgenizin ismi "Rehberim.txt" Bunu "Rehberim.csv" olarak değiştirim.
- Uzantısını değiştirdiğiniz dosyayı RehberProgramı.exe ile aynı klasörün içine koyun.
- RehberProgramı.exe dosyasını çalıştırın.
- Dosyanızın ismini uzantı olmadan girin.
    - Örnek: Dosyanızın ismi Rehberim.csv diyelim. O zaman Program çalıştığında Rehberim girmelisiniz.
- İki dosya oluşturulacaktır. Bunlardan ilki yine csv formatında dosyanızın alfabetik olarak sıralanmış halidir. İkincisi ise vcf formatında telefonunuza aktarabileceğiniz dosyadır.
- Daha fazla bilgi için [Açıklama Videosunu](https://youtu.be/w3-fggz-7UA "Telefon Rehberi Oluşturma") izleyebilirsiniz


### Linux
- Eğer Linux kullanıyorsanız zaten ne yapmanız gerektiğinizi biliyorsunuzdur :) Ancak ben kısaca bahsediyim.
- Windows'ta anlatılan gibi bir csv dosyası oluşturuyorsunuz.
- Şu komutu çalıştırıyorsunuz:
    ```bash
    sudo apt install make gcc
    ```
- Daha sonra Linux dizininin içine gidip:
    ```bash
    make
    ```
- Daha sonra ise programı çalıştırıyorsunuz:
    ```bash
    ./app
    ```

