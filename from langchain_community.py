from langchain_community.llms import Ollama
from langchain_community.vectorstores import Chroma
from langchain_community.embeddings import OllamaEmbeddings
from langchain_text_splitters import RecursiveCharacterTextSplitter
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.runnables import RunnablePassthrough
from langchain_core.output_parsers import StrOutputParser

# 1. Connect to your local Qwen
llm = Ollama(model="nomic-embed-text")

# 2. Set up embeddings (using a dedicated embedding model)
embeddings = OllamaEmbeddings(model="nomic-embed-text")

# 3. Your documents (can be anything — notes, PDFs, text)
documents = [
    "Faheem is a CS student at VIT Chennai studying AI.",
    "Qwen 13B is running locally for privacy reasons.",
    "The goal is to build impactful AI systems.",
]

# 4. Split documents into chunks
splitter = RecursiveCharacterTextSplitter(chunk_size=200, chunk_overlap=20)
chunks = splitter.create_documents(documents)

# 5. Store in ChromaDB (persisted locally on your machine)
vectorstore = Chroma.from_documents(
    documents=chunks,
    embedding=embeddings,
    persist_directory="./my_knowledge_base"
)

retriever = vectorstore.as_retriever()

# 6. Build the RAG chain
prompt = ChatPromptTemplate.from_template("""
Answer the question using only the context below.

Context: {context}

Question: {question}
""")

chain = (
    {"context": retriever, "question": RunnablePassthrough()}
    | prompt
    | llm
    | StrOutputParser()
)

# 7. Ask questions
response = chain.invoke("Why is Faheem running AI locally?")
print(response)