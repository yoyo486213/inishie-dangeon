from PIL import Image
import os

def flip_images_in_folder(input_folder, output_folder):
    # 確保輸出資料夾存在
    os.makedirs(output_folder, exist_ok=True)

    # 遍歷資料夾中的所有 PNG 圖片
    for filename in os.listdir(input_folder):
        if filename.endswith(".png"):
            image_path = os.path.join(input_folder, filename)
            output_path = os.path.join(output_folder, filename)

            # 打開圖片
            img = Image.open(image_path)

            # 進行左右反轉
            flipped_img = img.transpose(Image.FLIP_LEFT_RIGHT)

            # 保存反轉後的圖片
            flipped_img.save(output_path)
            print(f"反轉後的圖片已保存為: {output_path}")

# 使用範例
flip_images_in_folder(
    "C:/Users/yoyo/Desktop/Project/inishie-dangeon/ptsd-template-main/Resources/Map/Chest/Boxprogress",
    "C:/Users/yoyo/Desktop/Project/inishie-dangeon/ptsd-template-main/Resources/Map/Chest/Boxprogressbox"
)
