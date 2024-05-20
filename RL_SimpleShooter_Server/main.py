import time
import collections
import random

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

from Communication import Init

Send_Buffer = []
Receive_Buffer = []

Init(Send_Buffer, Receive_Buffer)

