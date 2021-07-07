import string
import nltk
from nltk.corpus import twitter_samples
from nltk.corpus import stopwords


def extract_effective_information(sentence):
    effective_words = []
    lemmatizer = nltk.WordNetLemmatizer()
    for word in sentence:
        new_word = lemmatizer.lemmatize(word)
        if new_word not in string.punctuation and new_word.lower() not in stopwords.words('english'):
            effective_words.append(new_word.lower())
    return effective_words


if __name__ == '__main__':
    # nltk.download()
    positive_sentences = twitter_samples.tokenized('positive_tweets.json')
    negative_sentences = twitter_samples.tokenized('negative_tweets.json')
    positive_effective = []
    negative_effective = []
    for st in positive_sentences:
        positive_effective.append(extract_effective_information(st))
    for st in negative_sentences:
        negative_effective.append(extract_effective_information(st))

    model_data = []
    for sentence in positive_effective:
        data_dict = dict([word, True] for word in sentence)
        model_data.append((data_dict, 'Positive'))
    for sentence in negative_effective:
        data_dict = dict([word, True] for word in sentence)
        model_data.append((data_dict, 'Negative'))
    model = nltk.NaiveBayesClassifier.train(model_data)

    while True:
        print("\n请输入一句话（或者输入exit退出）")
        sentence = input()
        if (sentence == "exit"):
            break
        words = nltk.word_tokenize(sentence)
        print(words)  # 输出分词信息
        words_effective = extract_effective_information(words)
        words = dict([word, True] for word in words_effective)
        result = model.classify(words)
        print('情绪推测: {}'.format(result))  # 输出情绪
