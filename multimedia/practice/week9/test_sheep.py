import os

import torch
from torch import nn
from torch.autograd import Variable
from torch.utils.data import DataLoader, random_split

import torchvision.utils as utils
import torchvision.datasets as dsets
import torchvision.transforms as transforms

import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

from model.LeNet import LeNet

if __name__ == '__main__':

    # gpu 설정
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

    # 모델 생성
    model = LeNet(_input_channel=, num_class=)
    model.to(device)

    criterion = nn.CrossEntropyLoss()

    # 테스트 할 모델 체크포인트 경로
    # 빈 칸 채우기
    test_checkpoint = ''

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
    # SheepFaceImages dataset

    # 이미지 변형
    transform_test = transforms.Compose([
        transforms.Resize([ , ], interpolation=Image.BICUBIC),
        transforms.ToTensor()
    ])

    # 데이터셋 로드
    test_data = dsets.ImageFolder('data/SheepFaceImages/test/', transform=transform_test)

    # 데이터로더 생성
    test_loader = torch.utils.data.DataLoader(
                    dataset=test_data,
                    batch_size=batch_size,
                    shuffle=False)
    #------------------------------------------

    test_loss = 0.0
    test_accuracy = 0.0

    model.eval()
    with torch.no_grad():
        for x, target in test_loader:
            x = x.to(device)
            target = target.to(device)
            
            # 모델에 입력
            # 빈 칸 채우기

            # loss 계산
            # 빈 칸 채우기
            loss = criterion(    )
            test_loss = test_loss + loss.item()

            # accuracy 계산
            output_label = torch.argmax(out, 1).to('cpu').numpy()
            target_label = target.to('cpu').numpy()

            correct_num = 0.0

            for index in range(len(target_label)):
                answer = target_label[index]
                predict = output_label[index]
                if answer == predict:
                    correct_num = correct_num + 1.0
            accuracy = correct_num / batch_size
            test_accuracy = test_accuracy + accuracy

        avg_test_loss = test_loss / len(test_loader)
        avg_test_accuracy = test_accuracy / len(test_loader)

        print('test loss : %f' % (avg_test_loss))
        print('test accuracy : %f' % (avg_test_accuracy))