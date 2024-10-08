def vigenere_encrypt(plain_text, key):
    encrypted_text = []
    key_length = len(key)
    
    for i, char in enumerate(plain_text):
        if char.isalpha():
            shift = ord(key[i % key_length].lower()) - ord('a')
            if char.isupper():
                encrypted_text.append(chr((ord(char) - ord('A') + shift) % 26 + ord('A')))
            else:
                encrypted_text.append(chr((ord(char) - ord('a') + shift) % 26 + ord('a')))
        else:
            encrypted_text.append(char)
    
    return ''.join(encrypted_text)

def vigenere_decrypt(cipher_text, key):
    decrypted_text = []
    key_length = len(key)
    
    for i, char in enumerate(cipher_text):
        if char.isalpha():
            shift = ord(key[i % key_length].lower()) - ord('a')
            if char.isupper():
                decrypted_text.append(chr((ord(char) - ord('A') - shift) % 26 + ord('A')))
            else:
                decrypted_text.append(chr((ord(char) - ord('a') - shift) % 26 + ord('a')))
        else:
            decrypted_text.append(char)
    
    return ''.join(decrypted_text)

def main():
    operation = input("Enkripsi atau Dekripsi? (e/d): ").lower()
    key = input("Masukkan Key: ").lower()
    text = input("Masukkan Plaintext / Ciphertext: ")

    if operation == 'e':
        encrypted = vigenere_encrypt(text, key)
        print("Encrypted text:", encrypted)
    elif operation == 'd':
        decrypted = vigenere_decrypt(text, key)
        print("Decrypted text:", decrypted)
    else:
        print("Invalid operation. Please choose 'e' to encrypt or 'd' to decrypt.")

if __name__ == "__main__":
    main()
