# Author: xalanq
# Email: xalanq@gmail.com
# License: LGPL v3.0

import sys, random, os
import tensorflow as tf
import numpy as np
from scipy.misc import imread, imsave, imresize
import matplotlib.pyplot as plt
from sklearn.metrics import roc_curve, auc


IMAGE_WIDTH = 200       # 图片宽度
IMAGE_HEIGHT = 200      # 图片高度
BATCH_SIZE = 32         # 一个batch大小
TEST_STEP = 50          # 几步就测一遍测试集
CKPT_STEP = 1000        # 几步模型就保存一次
CKPT_DIR = 'model/'     # 模型保存
LOG_DIR = 'log/'        # tensorboard数据
EPOCH = 100             # 数据复用次数
LEARNING_RATE = 1e-4    # 初始学习速率
KEEP_PROB = 0.5         # dropout参数


def new_weight(shape, name=None, stddev=0.1):
	w = tf.truncated_normal(shape=shape, stddev=stddev)
	return tf.Variable(w, name=name)


def new_bias(shape, name=None):
	b = tf.constant(value=0.1, shape=shape)
	return tf.Variable(b, name=name)


def cnn_model():
	global X, Y, keep_prob

	with tf.variable_scope('conv1-ReLU') as _:
		conv_1 = tf.nn.conv2d(X, new_weight([3, 3, 3, 32], 'filter'), strides=[1, 1, 1, 1], padding='SAME')
		conv_1 = tf.nn.bias_add(conv_1, new_bias([32], 'biases'))
		conv_1 = tf.nn.relu(conv_1, 'ReLU')

	conv_1 = tf.nn.max_pool(conv_1, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME', name='pool1-max')

	with tf.variable_scope('conv2-ReLU') as _:
		conv_2 = tf.nn.conv2d(conv_1, new_weight([3, 3, 32, 32], 'filter'), strides=[1, 1, 1, 1], padding='SAME')
		conv_2 = tf.nn.bias_add(conv_2, new_bias([32], 'biases'))
		conv_2 = tf.nn.relu(conv_2, 'ReLU')

	conv_2 = tf.nn.max_pool(conv_2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME', name='pool2-max')

	with tf.variable_scope('conv3-ReLU') as _:
		conv_3 = tf.nn.conv2d(conv_2, new_weight([3, 3, 32, 64], 'filter'), strides=[1, 1, 1, 1], padding='SAME')
		conv_3 = tf.nn.bias_add(conv_3, new_bias([64], 'biases'))
		conv_3 = tf.nn.relu(conv_3, 'ReLU')

	conv_3 = tf.nn.max_pool(conv_3, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME', name='pool3-max')

	with tf.variable_scope('dense1') as _:
		dense1 = tf.reshape(conv_3, [-1, IMAGE_WIDTH * IMAGE_HEIGHT])
		dense1 = tf.matmul(dense1, new_weight([dense1.get_shape()[1].value, 128], 'weights', 0.005)) + new_bias([128], 'biases')
		dense1 = tf.nn.relu(dense1, 'ReLU')
		dense1 = tf.nn.dropout(dense1, keep_prob, name='dropout')

	with tf.variable_scope('softmax_linear') as _:
		out = tf.matmul(dense1, new_weight([128, 2], 'weight')) + new_bias([2], 'biases')

	return out


def get_image(name):
	img = imread(name)
	w, h, _ = img.shape
	if IMAGE_WIDTH / w < IMAGE_HEIGHT / h:
		h = int(IMAGE_WIDTH / w * h)
		w = IMAGE_WIDTH
	else:
		w = int(IMAGE_HEIGHT / h * w)
		h = IMAGE_HEIGHT
	img = imresize(img, (w, h))
	img = img.astype(np.float32)
	img -= np.mean(img)
	res = np.zeros([IMAGE_WIDTH, IMAGE_HEIGHT, 3])
	res[:img.shape[0], :img.shape[1], :3] = img
	return res


def init():
	global X, Y, keep_prob
	X = tf.placeholder(tf.float32, [None, IMAGE_WIDTH, IMAGE_HEIGHT, 3])
	Y = tf.placeholder(tf.int32, [None, 2])
	keep_prob = tf.placeholder(tf.float32)


def train():
	global X, Y, keep_prob

	cnt = 0
	epoch = 0
	test_cnt = 0
	cat_name = [(x, 0) for x in list(map(lambda x: 'data/cat.{}.jpg'.format(x), list(range(0, 8000))))]
	dog_name = [(x, 1) for x in list(map(lambda x: 'data/dog.{}.jpg'.format(x), list(range(0, 8000))))]
	test_cat_name = [(x, 0) for x in list(map(lambda x: 'data/cat.{}.jpg'.format(x), list(range(8000, 10000))))]
	test_dog_name = [(x, 1) for x in list(map(lambda x: 'data/dog.{}.jpg'.format(x), list(range(8000, 10000))))]
	name = cat_name
	name.extend(dog_name)
	random.shuffle(name)
	test_name = test_cat_name
	test_name.extend(test_dog_name)
	random.shuffle(test_name)

	def next_batch(size):
		nonlocal cnt
		nonlocal epoch
		if epoch >= EPOCH:
			return None, None
		x = []
		y = []
		for i in range(size):
			p = (cnt + i) % len(name)
			x.append(get_image(name[p][0]))
			y.append([1 - name[p][1], name[p][1]])
		cnt = cnt + size
		if cnt + size >= len(name):
			epoch += 1
			cnt = cnt % len(name)
			random.shuffle(name)
		return x, y

	def next_test_batch(size):
		nonlocal test_cnt
		x = []
		y = []
		for i in range(size):
			p = (test_cnt + i) % len(test_name)
			x.append(get_image(test_name[p][0]))
			y.append([1 - test_name[p][1], test_name[p][1]])
		test_cnt = (test_cnt + size) % len(test_name)
		return x, y

	cnn = cnn_model()

	with tf.variable_scope('Loss') as _:
		loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=cnn, labels=Y), name='loss')
		tf.summary.scalar('softmax_cross_entropy', loss)

	optimizer = tf.train.AdamOptimizer(learning_rate=LEARNING_RATE).minimize(loss)

	with tf.variable_scope('Accuracy') as _:
		p1 = tf.argmax(cnn, 1)
		p2 = tf.argmax(Y, 1)
		accuracy = tf.reduce_mean(tf.cast(tf.equal(p1, p2), tf.float32), name='accuracy')
		tf.summary.scalar('train_and_test', accuracy)

	gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.9)
	with tf.Session(config=tf.ConfigProto(gpu_options=gpu_options)) as sess:
		summary = tf.summary.merge_all()
		train_logger = tf.summary.FileWriter(LOG_DIR + 'train', sess.graph)
		test_logger = tf.summary.FileWriter(LOG_DIR + 'test')

		sess.run(tf.global_variables_initializer())

		saver = tf.train.Saver(max_to_keep=5)
		ckpt = tf.train.latest_checkpoint(CKPT_DIR)
		if ckpt:
			saver.restore(sess, ckpt)
		step = 0
		while True:
			step += 1
			batch_x, batch_y = next_batch(BATCH_SIZE)
			if not batch_x:
				print("Done")
				break
			_, _loss, _acc, _s = sess.run([optimizer, loss, accuracy, summary], feed_dict={X: batch_x, Y: batch_y, keep_prob: KEEP_PROB})
			print('step: {}, loss: {:.3f}, accuracy: {:.3f}'.format(step, _loss, _acc))
			train_logger.add_summary(_s, global_step=step)
			if step % CKPT_STEP == 0:
				saver.save(sess, CKPT_DIR + 'model.ckpt', global_step=step)
			if step % TEST_STEP == 0:
				test_batch_x, test_batch_y = next_test_batch(BATCH_SIZE)
				s, acc = sess.run([summary, accuracy], feed_dict={X: test_batch_x, Y: test_batch_y, keep_prob: 1.0})
				print('(test set) accuracy: {:.3f}'.format(acc))
				test_logger.add_summary(s, global_step=step)


def judge(names, echo=True, prob=False):
	global keep_prob
	pred = tf.nn.softmax(cnn_model())
	gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.9)
	l = []
	with tf.Session(config=tf.ConfigProto(gpu_options=gpu_options)) as sess:
		saver = tf.train.Saver()
		ckpt = tf.train.latest_checkpoint(CKPT_DIR)
		if ckpt:
			saver.restore(sess, ckpt)
		else:
			print("Failed to load model")
			return
		for i in range(0, len(names), BATCH_SIZE):
			k = min(len(names), i + BATCH_SIZE)
			batch_x = []
			for j in range(i, k):
				batch_x.append(get_image(names[j]))
			p = sess.run(pred, feed_dict={X: batch_x, keep_prob: 1.0})
			for j in range(i, k):
				if echo:
					print('{} : [cat: {:.3f}, dog: {:.3f}] -> {}'.format(names[j], p[j - i][0], p[j - i][1], 'cat' if p[j - i][0] > p[j - i][1] else 'dog'))
				if prob:
					l.append((p[j - i][0], p[j - i][1]))
				else:
					l.append(int(p[j - i][0] < p[j - i][1]))
	return l


def judge_set():
	test_cat_name = list(map(lambda x: 'data/cat.{}.jpg'.format(x), list(range(8000, 10000))))
	test_dog_name = list(map(lambda x: 'data/dog.{}.jpg'.format(x), list(range(8000, 10000))))
	test_cat_name.extend(test_dog_name)
	a = judge(test_cat_name, echo=False)
	sum = 0
	for i in range(0, 2000):
		sum += 1 - a[i]
	for i in range(2000, 4000):
		sum += a[i]
	print('accuracy: {:.3f}'.format(sum / 4000))
	return a[0:2000], a[2000:4000]


def roc():
	test_cat_name = list(map(lambda x: 'data/cat.{}.jpg'.format(x), list(range(8000, 10000))))
	test_dog_name = list(map(lambda x: 'data/dog.{}.jpg'.format(x), list(range(8000, 10000))))
	test_cat_name.extend(test_dog_name)
	a = judge(test_cat_name, echo=False, prob=True)
	fpr = dict()
	tpr = dict()
	fpr, tpr, _ = roc_curve([int(i >= 2000) for i in range(4000)], [a[i][1] for i in range(4000)]) # cat is 0, dog is 1
	roc_auc = auc(fpr, tpr)

	plt.figure()
	plt.plot(fpr, tpr, color='darkorange', lw=2, label='ROC curve (area = {:.2f})'.format(roc_auc))
	plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
	plt.xlim([0.0, 1.0])
	plt.ylim([0.0, 1.05])
	plt.xlabel('False Positive Rate')
	plt.ylabel('True Positive Rate')
	plt.title('Receiver operating characteristic')
	plt.legend(loc="lower right")
	plt.show()


def feature():
	global X, keep_prob
	pred = tf.nn.softmax(cnn_model())
	gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.9)
	img = [get_image('data/cat.9967.jpg')]
	with tf.Session(config=tf.ConfigProto(gpu_options=gpu_options)) as sess:
		saver = tf.train.Saver()
		ckpt = tf.train.latest_checkpoint(CKPT_DIR)
		if ckpt:
			saver.restore(sess, ckpt)
		else:
			print("Failed to load model")
			return
		filter = tf.get_default_graph().get_tensor_by_name('conv1-ReLU/filter:0')
		biases = tf.get_default_graph().get_tensor_by_name('conv1-ReLU/biases:0')
		conv_1 = tf.nn.conv2d(X, filter, strides=[1, 1, 1, 1], padding='SAME')
		conv_1 = tf.nn.bias_add(conv_1, biases)
		out = sess.run(conv_1, feed_dict={X: img})
		for i in range(32):
			imsave('{}.jpg'.format(i), out[0, :, :, i])


if __name__ == '__main__':
	init()
	# judge_set()
	# roc()
	# feature()
	if len(sys.argv) > 1:
		judge(sys.argv[1:])
	else:
		train()
