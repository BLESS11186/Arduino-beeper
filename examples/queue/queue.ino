#define QUEUE_MAX_LEN 5
class Queue
{
  int queue[QUEUE_MAX_LEN];
  int top;
  int bottom;
  int s;

  public:
  Queue(){
    top = 0;
    bottom = 0;
    s = 0;
  }
  int getSize(){
    return s;
  }
  bool isEmpty(){
    return s==0;
  }
  bool push(int v){
    if(s >= QUEUE_MAX_LEN) return false;
    queue[bottom++] = v;
    if(bottom == QUEUE_MAX_LEN) bottom = 0;
    s++;
    return true;
  }
  int pop(){
    if(isEmpty()) return 0;
    int ret = queue[top++];
    if(top == QUEUE_MAX_LEN) top = 0;
    s--;
    return ret;
  }
  void printQueue(){
    Serial.println("====================");
    Serial.print("size is ");
    Serial.println(s);
    for(int i=0; i<QUEUE_MAX_LEN; i++){
      Serial.print(queue[i]);
      if(i == top) Serial.print("\ttop");
      if(i==bottom) Serial.print("\tbottom");
      Serial.println("");
    }
    Serial.println("====================");
  }
};

Queue q;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  q.push(100);
  q.push(200);
  q.push(300);
  q.printQueue();
  Serial.print("pop :");
  Serial.println(q.pop());
  Serial.print("pop :");
  Serial.println(q.pop());
  q.push(400);
  q.printQueue();
  q.push(500);
  q.printQueue();
  q.push(600);
  q.printQueue();
  Serial.print("pop :");
  Serial.println(q.pop());
  Serial.print("pop :");
  Serial.println(q.pop());
  Serial.print("pop :");
  Serial.println(q.pop());
  Serial.print("pop :");
  Serial.println(q.pop());
  q.printQueue();
}

void loop() {
  // put your main code here, to run repeatedly:

}
