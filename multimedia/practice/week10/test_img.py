import os

import torch
from torch import nn
from torch.autograd import Variable
from torch.utils.data import DataLoader, random_split

import torchvision.utils as utils
import torchvision.datasets as dsets
import torchvision.transforms as transforms

import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

from model.ResNet import *

def load_image(path:str):
    with open(path, 'rb') as f:
        img = Image.open(f)
        return img.convert('RGB')

if __name__ == '__main__':

    # gpu 설정
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

    # 모델 생성
    model = resnet18()
    model.to(device)

    criterion = nn.CrossEntropyLoss()

    # 테스트 할 모델 경로
    test_checkpoint = 'checkpoints/30_checkpoint.pth'

    #------------------------------------------
    # 이전 체크포인트로부터 모델 로드
    print("start model load...")
    # 체크포인트 로드
    checkpoint = torch.load(test_checkpoint, map_location=device)

    # 각종 파라미터 로드
    model.load_state_dict(checkpoint['model'])
    batch_size = checkpoint['batch_size']

    print("model load end.")
    #------------------------------------------

    #------------------------------------------
    # 테스트할 이미지 로드
    img_path = "data/sheep_test/Marino.jpg"
    test_img = load_image(img_path)
    plt.imshow(test_img, cmap='gray')
    plt.show()

    # 이미지 변환
    transform = transforms.Compose([
        transforms.Resize([120,120], interpolation=Image.BICUBIC),
        transforms.ToTensor()
    ])

    test_img = transform(test_img)
    #------------------------------------------

    # 결과 추론
    model.eval()

    test_input_img = test_img.unsqueeze(0)
    test_input_img = test_input_img.to(device)

    output = model(test_input_img)

    # 추론 결과
    print("클래스 별 확률:", output.cpu().detach().numpy())
    print("최종 예측: ", torch.argmax(output, 1).to('cpu').numpy())