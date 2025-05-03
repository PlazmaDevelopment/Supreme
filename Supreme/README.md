# Supreme

Supreme, Wholf Script için güçlü bir environment kütüphanesidir.

## Özellikler

- Çevre değişkenleri yönetimi
- Depolama sistemi
- Betik ayrıştırma
- Kaynak yükleyici
- Kullanıcı etkileşimi
- Olay yönetimi
- Performans optimizasyonları

## Kurulum

```wholf
fort import "Supreme"
```

## Kullanım

### Temel Kullanım

```wholf
// Çevre değişkeni ekleme
fegn Supreme {
    addVariable: ("test", "value") => {
        Console.log("Çevre değişkeni eklendi")
    }
}

// Depolama ekleme
fegn Supreme {
    addStorage: ("key", "value", "MEMORY") => {
        Console.log("Depolama eklendi")
    }
}

// Betik ekleme
fegn Supreme {
    addCommand: ("command", ["arg1", "arg2"], "WHOLF") => {
        Console.log("Betik eklendi")
    }
}

// Kaynak yükleme
fegn Supreme {
    loadResource: ("id", "path", "IMAGE") => {
        Console.log("Kaynak yüklendi")
    }
}

// Kullanıcı girişi
fegn Supreme {
    setUserInput: ("name", "value") => {
        Console.log("Kullanıcı girişi alındı")
    }
}
```

### Olay Yönetimi

```wholf
// Çevre değişkeni değiştiğinde
fegn Supreme {
    onVariableChange: ("test", callback) => {
        Console.log("Çevre değişkeni değişti")
    }
}

// Depolama değiştiğinde
fegn Supreme {
    onStorageChange: ("key", callback) => {
        Console.log("Depolama değişti")
    }
}

// Betik çalıştırıldığında
fegn Supreme {
    onCommand: ("command", callback) => {
        Console.log("Betik çalıştırıldı")
    }
}

// Kaynak yüklendiğinde
fegn Supreme {
    onResourceLoad: ("id", callback) => {
        Console.log("Kaynak yüklendi")
    }
}

// Kullanıcı etkileşimi
fegn Supreme {
    onUserEvent: ("name", callback) => {
        Console.log("Kullanıcı etkileşimi")
    }
}
```

## Lisans

MIT License
