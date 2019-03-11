Program pozwala na przetwarzanie obrazów za pomocą popularnych filtrów.
Program przyjmuje pięć argumentów. Jeśli użytkownik poda inną liczbę argumentów, program wyświetli odpowiedni komunikat i zakończy się. Pierwszy z nich to tryb filtra. –b oznacza korzystanie z filtra wbudowanego w program, –c oznacza wykorzystanie filtra stworzonego przez użytkownika (w postaci pliku tekstowego z macierzą, np:
1 3 5
4 5 6
4 5 9
). Drugim parametrem jest rozmiar (szerokość) wykorzystywanej maski. Wartość ta musi być nieparzysta, jeżeli użytkownik poda wartość parzystą program wyświetli odpowiedni komunikat i zakończy się. Trzeci parametr w zależności od trybu zawiera nazwę wbudowanego filtra (dla –b) lub ścieżkę dostępu do maski stworzonej przez użytkownika (dla -c). Dwa ostatnie parametry to ścieżki dostępu kolejnodo odczytywanego obrazu oraz do miejsca docelowego dla nowego pliku.
Przykład wywołania:
D:\Filtering\x64\Debug>Filtering.exe -b 3 high d:\lena.jpg d:\lena.jpg
